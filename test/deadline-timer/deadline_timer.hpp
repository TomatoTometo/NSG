#ifndef NSG_DEADLINE_TIMER_HPP_
#define NSG_DEADLINE_TIMER_HPP_

#include <atomic>
#include <cstddef>
#include <functional>
#include <time.h>

namespace nsg
{

class DeadlineTimer
{
public:

  /// Don't allow copies
  DeadlineTimer (const DeadlineTimer&) = delete;
  DeadlineTimer& operator= (const DeadlineTimer&) = delete;

  DeadlineTimer(const uint16_t hertz, std::function<void(size_t)> callback) 
    : m_callback(callback),
      m_time_interval(static_cast<uint64_t>((1.0 / hertz) * 1.0e9))
  {
  }

  void run()
  {
    m_activate.store(true);

    size_t failed_intervals = 0;

    struct timespec spec;
    clock_gettime(CLOCK_MONOTONIC, &spec);

    uint64_t curr_time = to_long(spec);
    uint64_t set_time = to_long(spec);
    
    do
    {
      /// Expected wake up time
      set_time += m_time_interval;

      /// Execute
      m_callback(failed_intervals);
      
      /// Update
      failed_intervals = 0;

      clock_gettime(CLOCK_MONOTONIC, &spec);
      curr_time = to_long(spec);

      /// Determine if timing was met, otherwise adjust
      if (set_time > curr_time)
      {
        curr_time = curr_time + (set_time - curr_time);
      }
      else
      {
        failed_intervals = ((curr_time - set_time) / m_time_interval) + 1;

        curr_time = set_time + (m_time_interval * failed_intervals);
      }

      /// Sleep
      set_time = curr_time;
      spec = to_timespec(set_time);
      clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &spec, NULL);
    } while(m_activate.load());
  }

  void stop()
  {
    m_activate.store(false);
  }

private:

  inline uint64_t to_long(struct timespec& t)
  {
    return ((t.tv_sec * 1e9) + t.tv_nsec);
  }

  inline struct timespec to_timespec(uint64_t t)
  {
    struct timespec spec;

    spec.tv_sec = t / 1e9;
    spec.tv_nsec = (t >= 1e9) ? (t - (spec.tv_sec * 1e9)) : t;

    return spec;
  }

  std::atomic<bool> m_activate;
  const uint64_t m_time_interval;

  std::function<void(size_t)> m_callback;
};

} // end namespace nsg

#endif // NSG_DEADLINE_TIMER_HPP_

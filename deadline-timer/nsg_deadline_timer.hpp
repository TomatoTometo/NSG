
////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <chrono>
#include <iomanip>
#include <thread>
#include <functional>

#include <atomic>
#include <cstddef>
#include <time.h>

class FooTimer
{
public:

  FooTimer(const uint16_t hertz, std::function<void(size_t)> func_) 
    : func(func_)
  {
    time_interval = static_cast<uint64_t>((1.0 / hertz) * 1e9);

    std::cout << "Time interval is " << time_interval << std::endl;
  }

  bool activate()
  {
    if(func)
    {
      active.store(true);
      return true;
    }
    
    return false;
  }

  void run()
  {
    size_t failed_intervals = 0;

    struct timespec curr_time;
    struct timespec prev_time;
    clock_gettime(CLOCK_MONOTONIC, &prev_time);
    
    for(int i = 0; i < 10; i++)
    // do
    {
      prev_time.tv_nsec = prev_time.tv_nsec + time_interval;
      // Correct range
      correct_timespec(prev_time);

      func(failed_intervals);
      
      failed_intervals = 0;

      clock_gettime(CLOCK_MONOTONIC, &curr_time);

      // current time is behind in seconds
      if(curr_time.tv_sec < prev_time.tv_sec)
      {
        curr_time.tv_sec = prev_time.tv_sec;
        curr_time.tv_nsec = prev_time.tv_nsec;
      }
      else // current seconds is equal or ahead to previous
      { 
        if (curr_time.tv_nsec > prev_time.tv_nsec)
        {
            failed_intervals = ((curr_time.tv_nsec - prev_time.tv_nsec) / time_interval) + 1;
            prev_time.tv_nsec = (prev_time.tv_nsec + (time_interval * (failed_intervals)));
            correct_timespec(prev_time);
        }

        // If current time is ahead in seconds, get add more to the failed intervals
        if(curr_time.tv_sec > prev_time.tv_sec)
        {
            failed_intervals += (((curr_time.tv_sec - prev_time.tv_sec) * 1e9) / time_interval);
        }

        // update the next sleep
        curr_time.tv_nsec = prev_time.tv_nsec;
      }

      prev_time = curr_time;
      clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &curr_time, NULL);
    } //while(active.load());
  }

  void stop()
  {
    active.store(false);
  }

private:

  inline void correct_timespec(struct timespec& t)
  {
    if(t.tv_nsec > 999999999)
    {
        t.tv_sec++;
        t.tv_nsec -= 999999999;
    }
  }

  std::atomic<bool> active;
  long time_interval;

  std::function<void(size_t)> func;
};

int main(int argc, char** argv)
{
double pi = 3.145416;
const auto bar =  [&pi](size_t intervals)
 {
     static int counter = 0;
     static int missed = 0;
     static double prev = std::chrono::steady_clock::now().time_since_epoch().count() / 1e9;
     
    // static auto start = std::chrono::steady_clock::now();
    if(intervals)
        std::cout << "Missed intervals " << intervals << std::endl;

    auto end = std::chrono::steady_clock::now();
    double now = (end.time_since_epoch().count() / 1e9);
    // std::chrono::duration<double> diff = end - start;
    // if ((now - prev) > 0.0003000000000000000)
    // {
    //     missed++;
    //     // std::cout << "Time " << std::fixed << std::setprecision(10) << (now - prev) << " s\n";
    // }

    std::cout << "Time " << std::fixed << std::setprecision(10) << (now - prev) << " s\n";
    
    if (counter++ >= 9)
    {
        std::cout << "Missed these many  " << missed << " s\n";
    }
    prev = now;

    static int once = 0;
    if(once++ == 2)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

 };

 FooTimer foo(10,bar);
 foo.activate();

 foo.run();
    
// auto start = std::chrono::system_clock::now();
//     foo(&fern);
//     // std::thread t1(bar, &fern);
//     // std::thread t2(foo, &fern);
//     // t1.join();
//     // t2.join();    
// auto end = std::chrono::system_clock::now();
//     bar(&fern);

// std::chrono::duration<double> diff = end - start;
// std::cout << "Time " << diff.count() << " s\n";
    return 0;
}

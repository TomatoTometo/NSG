#ifndef NSG_COUNTING_SEMAPHORE_HPP_
#define NSG_COUNTING_SEMAPHORE_HPP_

#include <condition_variable>
#include <mutex>
#include <limits>
#include <cstddef>

namespace nsg
{

template<size_t MAX_POST = std::numeric_limits<size_t>::max()>
class CountingSemaphore
{

public:

  ////////////////////////////////////////////////////////////////////////////////////////////////
  /// @brief Notifies the waiting thread, it can notify up to MAX_POST times
  /// @return True on a successful notify, false otherswise
  bool post() 
  {
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_count >= MAX_POST)
    {
      return false;
    }

    ++m_count;
    m_condition.notify_one();

    return true;
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////
  /// @brief Waits on a notification
  /// @return Amount of counts that need to be processed
  size_t wait() 
  {
    std::unique_lock<std::mutex> lock(m_mutex);

    if(m_count > 0)
    {
      return (--m_count);
    }

    m_condition.wait(lock, [this]
    {
      return (m_count > 0);
    });

    return (--m_count);
  }

private:

  std::mutex m_mutex;
  std::condition_variable m_condition;

  size_t m_count = 0;
};

} // end namespace nsg

#endif // NSG_COUNTING_SEMAPHORE_HPP_
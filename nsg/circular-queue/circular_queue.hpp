#ifndef NSG_CIRCULAR_QUEUE_HPP_
#define NSG_CIRCULAR_QUEUE_HPP_

#include <algorithm>
#include <array>
#include <atomic>
#include <cstddef>
#include <functional>

namespace nsg
{

////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Basically a poor man's attempt at a circular queue. This can also be used a a 
///        single producer single consumer queue
////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, size_t size>
class CircularQueue
{
public:
  
  /// Don't allow copies
  CircularQueue (const CircularQueue&) = delete;
  CircularQueue& operator= (const CircularQueue&) = delete;

  ////////////////////////////////////////////////////////////////////////////////////////////////
  CircularQueue(T init_val = T{}) : 
    m_start{0}, 
    m_end{0}, 
    QUEUE_SIZE{size + 1}
  {
    std::fill(std::begin(m_array), std::end(m_array), init_val);
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////
  /// @brief Simply pushes `data` into the queue
  /// @param data Data to be pushed into the queue
  /// @param callback Optional callback used when pushing to the queue
  /// @return True if sucessfully pushed to queue, false otherwise
  bool push(T& data, std::function<void(const T&, T&)> callback = nullptr)
  {
    const size_t end = m_end.load();
    const size_t next_end = (end + 1) % QUEUE_SIZE;

    // Space available?
    if(next_end != m_start.load())
    {
      if (callback)
      {
        callback(data, m_array[end]);
      }
      else
      {
        m_array[end] = data;
      }

      m_end.store(next_end);
      return true;
    }

    // It's full
    return false;
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////
  /// @brief Simply pops `data` from the queue
  /// @param data Output data copied from the queue
  /// @param callback Optional callback used when poping from the queue
  /// @return True if sucessfully popped from queue, false otherwise
  bool pop(T& data, std::function<void(const T&, T&)> callback = nullptr)
  {
    const size_t start = m_start.load();
    if(start == m_end.load())
    {
      // Nothing to pop
      return false;
    }

    // Pop
    if(callback)
    {
      callback(m_array[start], data);
    }
    else
    {
      data = std::move(m_array[start]);
    }

    m_start.store((start + 1) % QUEUE_SIZE);

    return true;
  }

private:
  std::atomic<size_t> m_start;
  std::atomic<size_t> m_end;

  const size_t QUEUE_SIZE;

  std::array<T, size + 1> m_array;
};

} // end namespace nsg

#endif // NSG_CIRCULAR_QUEUE_HPP_

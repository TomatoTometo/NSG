#ifndef NSG_CIRCULAR_QUEUE_HPP_
#define NSG_CIRCULAR_QUEUE_HPP_

#include <algorithm>
#include <array>
#include <atomic>
#include <cstddef>

namespace nsg
{

////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Basically a poor man's attempt at a circular queue
///        The idea is to simply have the `push` drive the back of the queue
///        while `pop` drives the front. It synchronizes these calls with the help
///        of std::atomic.
///        
///        The size of the queue will be the size provided + 1 but it will only hold
///        `size` valid entries
///        
///        The queue is thread safe in the sense of having one thread pushing while another
///        thread pops. It is NOT thread safe if there are multiple threads pushing or multiple
///        threads popping. In such case, I suggest guarding the push or pop wih a mutex
////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, size_t size>
class CircularQueue
{
private:
  /// Copy function signature
  typedef void (*Cpy_Func)(const T&, T&);

public:

  ////////////////////////////////////////////////////////////////////////////////////////////////
  CircularQueue(T init_val = T{}) : 
    start{0}, 
    end{0}, 
    ACTUAL_SIZE{size + 1}
  {
    std::fill(std::begin(arr), std::end(arr), init_val);
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////
  /// @brief Simply pushes `data` into the queue
  /// @param data Data to be pushed into the queue
  /// @param copy_data Optional function to use when copying data.
  ///                  The function signature is void(T& source, T& destination)
  /// @return True if sucessfully pushed to queue, false otherwise
  bool push(T& data, Cpy_Func copy_data = nullptr)
  {
    const size_t end_ = end.load();
    const size_t next_end_ = (end_ + 1) % ACTUAL_SIZE;

    // Space available?
    if(next_end_ != start.load())
    {
      if (copy_data)
      {
        copy_data(data, arr[end_]);
      }
      else
      {
        arr[end_] = data;
      }

      end.store(next_end_);
      return true;
    }

    // It's full
    return false;
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////
  /// @brief Simply pops `data` from the queue
  /// @param data Output data copied from the queue
  /// @param copy_data Optional function to use when copying data.
  ///                  The function signature is void(T& source, T& destination)
  /// @return True if sucessfully popped from queue, false otherwise
  bool pop(T& data, Cpy_Func copy_data = nullptr)
  {
    const size_t start_ = start.load();
    if(start_ == end.load())
    {
      // Nothing to pop
      return false;
    }

    // Pop
    if(copy_data)
    {
      copy_data(arr[start_], data);
    }
    else
    {
      data = std::move(arr[start_]);
    }

    start.store((start_ + 1) % ACTUAL_SIZE);

    return true;
  }

private:
  std::atomic<size_t> start;
  std::atomic<size_t> end;

  const size_t ACTUAL_SIZE;

  std::array<T, size + 1> arr;
};

} // end namespace nsg

#endif // NSG_CIRCULAR_QUEUE_HPP_

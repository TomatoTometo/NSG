
////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <chrono>
#include <iomanip>
#include <thread>
// #include <string.h>
// #include <vector>
// #include <memory>

#include <atomic>
#include <cstddef>
#include <time.h>
/*
struct timespec deadline;
clock_gettime(CLOCK_MONOTONIC, &deadline);

// Add the time you want to sleep
deadline.tv_nsec += 1000;

// Normalize the time to account for the second boundary
if(deadline.tv_nsec >= 1000000000) {
    deadline.tv_nsec -= 1000000000;
    deadline.tv_sec++;
}
clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &deadline, NULL);


time_t tv_sec	whole seconds (valid values are >= 0)
long tv_nsec	nanoseconds (valid values are [0, 999999999])

*/
class FooTimer
{
private:

  typedef void (*Process_Func_Ptr)(size_t);

public:

  FooTimer(const double hertz, Process_Func_Ptr func_) 
    : func(func_)
  {
    time_interval = static_cast<long>((1.0 / hertz) * 1e9);

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
 auto start = std::chrono::steady_clock::now();
      prev_time.tv_nsec = prev_time.tv_nsec + time_interval;

      correct_timespec(prev_time);

      func(failed_intervals);
      failed_intervals = 0;

      clock_gettime(CLOCK_MONOTONIC, &curr_time);

      if(curr_time.tv_sec < prev_time.tv_sec)
      {
        curr_time.tv_sec = prev_time.tv_sec;
        curr_time.tv_nsec = prev_time.tv_nsec;
      }
      else
      { 
        if(curr_time.tv_nsec <= prev_time.tv_nsec)
        {
            curr_time.tv_nsec = prev_time.tv_nsec;
        }
        else
        {
            // std::cout << "here " << __LINE__ <<std::endl;
            // std::cout << "curr_time.tv_sec " << curr_time.tv_sec <<std::endl;
            // std::cout << "curr_time.tv_nsec " << curr_time.tv_nsec <<std::endl;
            // std::cout << "prev_time.tv_sec " << prev_time.tv_sec <<std::endl;
            // std::cout << "prev_time.tv_nsec " << prev_time.tv_nsec <<std::endl;
            failed_intervals = ((curr_time.tv_nsec - prev_time.tv_nsec) / time_interval) + 1;
            prev_time.tv_nsec = (prev_time.tv_nsec + (time_interval * (failed_intervals)));

            correct_timespec(prev_time);
        }

        // failed seconds
        failed_intervals += (((curr_time.tv_sec - prev_time.tv_sec) * 1e9) / time_interval);
        curr_time.tv_nsec = prev_time.tv_nsec;
      }

      prev_time = curr_time;
      clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &curr_time, NULL);
auto end = std::chrono::steady_clock::now();
std::chrono::duration<double> diff = end - start;
std::cout << "----Time " << std::fixed << std::setprecision(10) << diff.count() << " s\n";
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

  Process_Func_Ptr func;
};

int main(int argc, char** argv)
{

const auto bar =  [](size_t intervals)
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
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

 };

 FooTimer foo(1440,bar);
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

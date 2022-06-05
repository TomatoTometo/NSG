#include <gtest/gtest.h>

#include "nsg/circular-queue/circular_queue.hpp"

TEST(NSGCircularQueueTest, AllTestInOne)
{
  nsg::CircularQueue<int, 10> queue;

  // Can push as long as there is space
  for(int i = 0; i < 10; ++i)
  {
    EXPECT_TRUE(queue.push(i));
  }

  // Can't push while its full
  EXPECT_FALSE(queue.push(10));

  int integer;
  // Can pop as long as there are values
  for(int i = 0; i < 10; ++i)
  {
    EXPECT_TRUE(queue.pop(integer));
  }

  // Can't pop while its full
  EXPECT_FALSE(queue.pop(integer));

  // Can push with lambda
  EXPECT_TRUE(queue.push(42, [](const int& src, int& dst)
  {
    dst = std::move(src);
  }));

  // Can pop with lambda
  EXPECT_TRUE(queue.pop(integer, [](const int& src, int& dst)
  {
    dst = std::move(src);
  }));

  EXPECT_EQ(integer, 42);
}

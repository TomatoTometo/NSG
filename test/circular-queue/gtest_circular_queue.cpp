#include <gtest/gtest.h>

#include "nsg/circular-queue/circular_queue.hpp"

class CircularQueueTest : public ::testing::Test
{
public:
  
  void SetUp() override 
  {
    /// Nothing
  }

  nsg::CircularQueue<int, 10> m_queue;
};


TEST_F(CircularQueueTest, CanBePushedInto) 
{
  EXPECT_TRUE(m_queue.push(42));
}

TEST_F(CircularQueueTest, CanBePopFrom) 
{
  EXPECT_TRUE(m_queue.push(42));
  
  int integer;
  EXPECT_TRUE(m_queue.pop(integer));

  EXPECT_EQ(integer, 42);
}

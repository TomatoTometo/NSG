#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace
{
/// @brief A silly recrusive binary search function
bool silly_binary_search(const uint32_t* data, const size_t size, const uint32_t value)
{
  // Bug here that will cause an infinite loop
  if (size == 0 /*|| size == 1*/)
  {
    return (*data == value);
  }

  const size_t mid = size / 2;
  const uint32_t* mid_ptr = (data + mid);

  if((*mid_ptr) == value)
  {
    return true;
  }
  else if ((*mid_ptr) > value)
  {
    return silly_binary_search(data, mid, value);
  }
  else
  {
    return silly_binary_search((mid_ptr), size - mid, value);
  }
}

} // end anonymous namespace

TEST(sillyBinarySearch, FindsValueTowardsEndOfData)
{
  uint32_t data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_TRUE(silly_binary_search(data, 10, 7));
}

TEST(sillyBinarySearch, FindsValueTowardsStartOfData)
{
  uint32_t data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_TRUE(silly_binary_search(data, 10, 3));
}

// DISABLED_ Allows you to disable the gtest from running
// but test will still be compiled
TEST(DISABLED_sillyBinarySearch, DoesNotFindValue)
{
  uint32_t data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  
  // Will cause infinite loop
  EXPECT_FALSE(silly_binary_search(data, 10, 15));
}

TEST(itemsInArray, areBiggerThanValue)
{
  uint32_t data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  for (size_t i = 0; i < 5; ++i)
  {
    EXPECT_THAT(data[i], ::testing::Lt(5)) << \
      "[MORE INFO] Test failed at i = " << i << "\n";
  }
}

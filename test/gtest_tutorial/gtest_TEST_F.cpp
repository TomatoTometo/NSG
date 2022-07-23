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

class sillyBinarySearch : public ::testing::Test
{
public:

  /// SetUp per Test Suite, usually for shared resources between Tests
  static void SetUpTestSuite()
  {
    std::cout <<"[    >>>   ] Here calling << " << __func__ << "!\n";
  }

  /// TearDown per Test Suite, usually for shared resources between Tests
  static void TearDownTestSuite()
  {
    std::cout <<"[    >>>   ] Here calling << " << __func__ << "!\n";
  }

protected:
  /// SetUp per Test
  void SetUp() override
  {
    std::cout <<"[    >>    ] Here calling << " << __func__ << "!\n";
  }

  /// TearDown per Test
  void TearDown() override
  {
    std::cout <<"[    >>    ] Here calling << " << __func__ << "!\n";
  }

  static constexpr size_t ARR_SIZE = 10;
  uint32_t data_[ARR_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
};

TEST_F(sillyBinarySearch, FindsValueTowardsEndOfData)
{
  EXPECT_TRUE(silly_binary_search(data_, ARR_SIZE, 7));
}

TEST_F(sillyBinarySearch, FindsValueTowardsStartOfData)
{
  EXPECT_TRUE(silly_binary_search(data_, ARR_SIZE, 3));
}

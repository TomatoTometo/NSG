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

class sillyBinarySearch : public testing::TestWithParam<uint32_t>
{

protected:

  static constexpr size_t ARR_SIZE = 10;
  uint32_t data_[ARR_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
};

MATCHER(IsEven, "") { return (arg % 2) == 0; }

TEST_P(sillyBinarySearch, FindsValueInData)
{
  const uint32_t value = GetParam();
  EXPECT_TRUE(silly_binary_search(data_, ARR_SIZE, value));
}

std::string my_print_function(const ::testing::TestParamInfo<uint32_t>& info)
{
  static uint32_t test_count = 1;
  return std::string("Test_") + std::to_string(test_count++) + std::string("_with_input_") + std::to_string(info.param);
}

// The first argument to INSTANTIATE_TEST_SUITE_P is a unique name for the instantiation of the test suite. 
// The next argument is the name of the test pattern, and the last is the parameter generator.
INSTANTIATE_TEST_SUITE_P(
  MySillyBinaryTestSuite,
  sillyBinarySearch,
  testing::Values(3, 4, 5, 9, 1, 10)//, my_print_function
);



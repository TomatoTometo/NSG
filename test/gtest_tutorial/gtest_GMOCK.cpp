#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>

namespace
{

// class Foo
// {
// public:

//   Foo()
//   {
//      // some weird FPGA ritual to initialize the registers
//   }

//   ~Foo() {}

//   void check_temperature()
//   {
//     bool good = true;
//     // Check signal A
//     if (*FPGA_REGISTER_TMP > 100)
//     {
//       good = false;
//     }

//     // Check signal B
//     if (*(FPGA_REGISTER_TMP + FPGA_REGISTER_SIG_OFFSET) > 50)
//     {
//       good = false;
//     }

//     if (!good)
//     {
//       // 0x00004500 Bits to turn off power
//       *FPGA_REGISTER_PWR = (*FPGA_REGISTER_PWR & ~(0x00004500));
//     }
//   }

// private:

//   // Made-belive FPGA addresses and an offset
//   // Temperature
//   uint32_t* FPGA_REGISTER_TMP = reinterpret_cast<uint32_t*>(0xBEBECAFE);
//   // Power
//   uint32_t* FPGA_REGISTER_PWR = (uint32_t*)0xBEBEBEEF;

//   uint32_t FPGA_REGISTER_SIG_OFFSET = 0x20;
// };

class HwIf
{
public:
 
  virtual ~HwIf() {}
  
  virtual void init(const uint32_t* ptr) = 0;
  virtual bool check_temperature() = 0;
  virtual void shutdown() = 0;
};

class MockHw : public HwIf 
{
public:

  MOCK_METHOD(void, init, (const uint32_t* ptr), (override));
  MOCK_METHOD(bool, check_temperature, (), (override));
  MOCK_METHOD(void, shutdown, (), (override));
};

class Foo
{
public:

  Foo(std::shared_ptr<HwIf> hw_if) : 
    hw_if_(std::move(hw_if))
  {
    hw_if_->init(nullptr);
  }

  ~Foo() {}

  void check_temp()
  {

    const bool good = hw_if_->check_temperature();

    if (!good)
    {
      hw_if_->shutdown();
    }
  }

private:

  std::shared_ptr<HwIf> hw_if_;
};

} // end anonymous namespace

class MockHwTest : public ::testing::Test
{
protected:
  /// SetUp per Test
  void SetUp() override
  {
    mock_hw_ = std::make_shared<MockHw>();

    EXPECT_CALL(*mock_hw_, init(::testing::_))
      .Times(::testing::Exactly(1));

    foo_obj_ = std::make_unique<Foo>(mock_hw_);
  }

  /// TearDown per Test
  void TearDown() override
  {
    mock_hw_.reset();
    foo_obj_.reset();
  }

  std::shared_ptr<MockHw> mock_hw_;
  std::unique_ptr<Foo> foo_obj_;
};

// TEST_F(MockHwTest, complainsIfNoExpectCall)
// {
//   foo_obj_->check_temp();
// }

TEST_F(MockHwTest, badTemperatures)
{
  EXPECT_CALL(*mock_hw_, check_temperature())
    .Times(::testing::AtLeast(1))
    .WillOnce(::testing::Return(false));

  EXPECT_CALL(*mock_hw_, shutdown())
    .Times(::testing::AtLeast(1));

  foo_obj_->check_temp();
}

TEST_F(MockHwTest, goodTemperatures)
{
  EXPECT_CALL(*mock_hw_, check_temperature())
    .Times(::testing::Exactly(1))
    .WillOnce(::testing::Return(true));

  EXPECT_CALL(*mock_hw_, shutdown())
    .Times(::testing::Exactly(0));

  foo_obj_->check_temp();
}

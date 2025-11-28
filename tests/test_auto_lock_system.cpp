#include "auto_lock_system.h"
#include "clock_interface.h"
#include <cstdint>
#include <gmock/gmock.h>

using ::testing::Return; // Để dùng được lệnh Return()

class MockClock : public IClock
{
  public:
    MOCK_METHOD(uint32_t, get_time, (), (const, override));
};

TEST(AutoLockSystemTest, ShoudlLockAfter5Seconds)
{
    MockClock mock;
    AutoLockSystem system(mock);

    EXPECT_CALL(mock, get_time()).WillOnce(Return(1000)).WillOnce(Return(7000)).WillRepeatedly(Return(2000));

    // bool isLockedFirst = system.update(25.0f);
    // EXPECT_FALSE(isLockedFirst);
    //
    // bool isLockedSecond = system.update(25.0f);
    // EXPECT_TRUE(isLockedSecond);

    EXPECT_EQ(mock.get_time(), 1000);
    EXPECT_EQ(mock.get_time(), 7000);
    EXPECT_EQ(mock.get_time(), 2000);
    EXPECT_EQ(mock.get_time(), 2000);
    EXPECT_EQ(mock.get_time(), 2000);
    EXPECT_EQ(mock.get_time(), 2000);
    EXPECT_EQ(mock.get_time(), 2000);
}

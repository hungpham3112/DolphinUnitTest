#include "auto_lock_system.h"
#include "clock_interface.h"
#include "gmock/gmock.h"
#include <cstdint>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::Return; // Để dùng được lệnh Return()

class MockClock : public IClock {
public:
  MOCK_METHOD(uint32_t, get_time, (), (const, override));
};

TEST(AutoLockSystemTest, ShoudlLockAfter5SecondsMock) {
  MockClock mock;
  AutoLockSystem system(mock);

  EXPECT_CALL(mock, get_time())
      .WillOnce(Return(1000))
      .WillOnce(Return(7000))
      .WillRepeatedly(Return(2000));

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

class StubClock : public IClock {
public:
  MOCK_METHOD(uint32_t, get_time, (), (const, override));
};

TEST(AutoLockSystemTest, ShoudlLockAfter5SecondsStub) {
  StubClock stub;
  AutoLockSystem system(stub);

  // --- CẤU HÌNH STUB (Configuration) ---
  // ON_CALL: Chỉ định nghĩa dữ liệu trả về, KHÔNG thiết lập kỳ vọng
  // (Expectation). Mặc định trả về 1000 (Thời điểm bắt đầu)
  ON_CALL(stub, get_time()).WillByDefault(Return(1000));

  // 2. ACT (Chạy logic)
  // Hệ thống gọi get_time(), nhận được 1000 (Default)
  system.update(25.0f);

  // --- THAY ĐỔI DỮ LIỆU STUB (Re-configuration) ---
  // Bây giờ muốn trả về 7000? Ghi đè lên hành vi cũ.
  ON_CALL(stub, get_time()).WillByDefault(Return(7000));

  // Hệ thống gọi get_time(), nhận được 7000
  bool isLocked = system.update(25.0f);

  // 3. ASSERT (State Verification)
  EXPECT_TRUE(isLocked);
}

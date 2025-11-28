#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>
#include <vector>

// ==========================================
// 1. THE ABSTRACTION (INTERFACE)
// ==========================================
class IMessenger {
public:
  virtual ~IMessenger() = default;
  virtual void send(const std::string &msg) = 0;
  virtual bool isConnected() const = 0;
};

// ==========================================
// 2. THE SYSTEM UNDER TEST (SUT)
// ==========================================
class AlertSystem {
  IMessenger &messenger; // Dependency Injection
public:
  AlertSystem(IMessenger &m) : messenger(m) {}

  // Hàm này KHÔNG dùng dependency (Dùng cho Dummy test)
  int calculateRiskLevel(int speed) {
    if (speed > 100)
      return 2; // High
    if (speed > 50)
      return 1; // Medium
    return 0;   // Low
  }

  // Hàm này DÙNG dependency (Dùng cho Stub, Spy, Mock, Fake)
  void sendAlert(const std::string &msg) {
    // Logic: Chỉ gửi nếu đang kết nối
    if (messenger.isConnected()) {
      messenger.send(msg);
    }
  }
};

// ==========================================
// 3. MANUAL TEST DOUBLES (C++ Pure)
// ==========================================

// TYPE 1: DUMMY (Người nộm)
// Mục đích: Chỉ để code biên dịch được (fill parameter). Không có logic.
class DummyMessenger : public IMessenger {
public:
  void send(const std::string &) override { /* Không làm gì */ }
  bool isConnected() const override { return false; /* Giá trị rác */ }
};

// TYPE 2: STUB (Người nhắc tuồng)
// Mục đích: Trả về trạng thái cố định (Hard-coded) để lái luồng if/else.
class StubMessenger : public IMessenger {
  bool is_connected_response;

public:
  StubMessenger(bool status) : is_connected_response(status) {}

  void send(const std::string &) override { /* Không quan tâm */ }

  // Logic Stub: Luôn trả về giá trị đã cài đặt sẵn
  bool isConnected() const override { return is_connected_response; }
};

// TYPE 3: SPY (Gián điệp)
// Mục đích: Ghi lại số lần gọi hàm (Side effect recording).
class SpyMessenger : public IMessenger {
public:
  int send_call_count = 0; // Sổ tay ghi chép

  // Logic Spy: Ghi lại hành vi
  void send(const std::string &) override { send_call_count++; }

  // Stub phần này để logic chạy được vào hàm send
  bool isConnected() const override { return true; }
};

// TYPE 4: FAKE (Hàng nhái cao cấp)
// Mục đích: Có logic hoạt động thật (lưu vào RAM) thay vì gửi Network thật.
class FakeMessenger : public IMessenger {
public:
  std::vector<std::string> inbox; // "Database" giả lập trong RAM

  // Logic Fake: Hoạt động như thật, lưu tin nhắn lại
  void send(const std::string &msg) override { inbox.push_back(msg); }
  bool isConnected() const override { return true; }
};

// TYPE 5: MOCK (Cảnh sát - Dùng Google Mock)
// Mục đích: Kiểm tra giao thức (Protocol) nghiêm ngặt.
class MockMessenger : public IMessenger {
public:
  MOCK_METHOD(void, send, (const std::string &), (override));
  MOCK_METHOD(bool, isConnected, (), (const, override));
};

// ==========================================
// 4. TEST SUITE (Gom nhóm các kịch bản)
// ==========================================

// Case 1: DUMMY
// Test hàm calculateRisk không liên quan gì đến Messenger.
// Nhưng constructor bắt buộc phải có Messenger -> Dùng Dummy.
TEST(TestDoubleSuite, Dummy_JustFillTheGap) {
  DummyMessenger dummy;
  AlertSystem system(dummy); // Tiêm Dummy vào

  // Chỉ test logic nội tại, không gọi method nào của dummy
  EXPECT_EQ(system.calculateRiskLevel(120), 2);
}

// Case 2: STUB
// Test logic if/else: Nếu mất kết nối thì không được gửi.
TEST(TestDoubleSuite, Stub_ControlFlow) {
  StubMessenger stub(false); // Cài đặt Stub luôn trả về FALSE (Mất kết nối)
  AlertSystem system(stub);

  // Act
  system.sendAlert("Danger!");

  // Assert: Ta không verify gì ở Stub cả, ta tin là logic if(false) đã chạy
  // đúng (Thực ra Stub yếu ở chỗ này, không biết hàm send có bị gọi nhầm không)
  SUCCEED();
}

// Case 3: SPY
// Test xem hàm send có được gọi đúng số lần không?
TEST(TestDoubleSuite, Spy_VerifyCallCount) {
  SpyMessenger spy;
  AlertSystem system(spy);

  system.sendAlert("Alert 1");
  system.sendAlert("Alert 2");

  // Assert Behavior (Manual verification)
  EXPECT_EQ(spy.send_call_count, 2);
}

// Case 4: FAKE
// Test xem nội dung tin nhắn có được lưu đúng không? (Functional Test)
TEST(TestDoubleSuite, Fake_VerifyDataIntegrity) {
  FakeMessenger fake;
  AlertSystem system(fake);

  system.sendAlert("Critical Error");

  // Assert State (Kiểm tra dữ liệu trong RAM của Fake)
  ASSERT_EQ(fake.inbox.size(), 1);
  EXPECT_EQ(fake.inbox[0], "Critical Error");
}

// Case 5: MOCK (GMock)
// Test giao thức nghiêm ngặt.
TEST(TestDoubleSuite, Mock_StrictProtocol) {
  MockMessenger mock;
  AlertSystem system(mock);

  using ::testing::_;
  using ::testing::Return;

  // EXPECTATION:
  // 1. isConnected phải được gọi trước.
  // 2. send phải được gọi đúng 1 lần với nội dung "Hello".
  EXPECT_CALL(mock, isConnected()).WillOnce(Return(true));
  EXPECT_CALL(mock, send("Hello")).Times(1);

  // Act
  system.sendAlert("Hello");
}

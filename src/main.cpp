#include "auto_lock_system.h"
#include "clock_interface.h"
#include <chrono>
#include <iostream>

class MockClock : public IClock {
  uint32_t fake_time_ = 0;

public:
  uint32_t get_time() const override { return fake_time_; }
  // Hàm này chỉ có ở Mock, Interface gốc không có
  void set_time(uint32_t t) { fake_time_ = t; }
};

// ==========================================
// 2. COMPOSITION ROOT (MAIN)
// ==========================================
int main() {
  std::cout << "--- DEMO DEPENDENCY INJECTION ---\n\n";

  // -------------------------------------------------
  // Kịch bản 1: Môi trường PRODUCTION
  // -------------------------------------------------
  std::cout << "[1] Production Context (Real Hardware)\n";

  // Bước 1: Chuẩn bị dependency thật
  RealClock realHardware;

  // Bước 2: INJECT vào hệ thống (Cắm phích thật)
  AutoLockSystem myProductionCar(realHardware);

  // Chạy thử logic
  // (Vì là đồng hồ thật, ta khó kiểm soát kết quả ở đây nếu không chờ đủ 5s)
  myProductionCar.update(25.0);
  std::cout << " -> System initialized with RealClock.\n\n";

  // -------------------------------------------------
  // Kịch bản 2: Môi trường TESTING
  // -------------------------------------------------
  std::cout << "[2] Testing Context (Mock Hardware)\n";

  // Bước 1: Chuẩn bị dependency giả
  MockClock fakeHardware;

  // Bước 2: INJECT vào hệ thống (Cắm phích giả)
  // Vẫn là class AutoLockSystem đó, nhưng hành vi giờ phụ thuộc vào Mock
  AutoLockSystem myTestCar(fakeHardware);

  // Bước 3: Thao túng thời gian để kiểm tra logic
  std::cout << " -> Injecting MockClock... Simulating 6 seconds passed.\n";

  fakeHardware.set_time(0);
  myTestCar.update(25.0); // Bắt đầu đếm giờ

  fakeHardware.set_time(6000);            // Tua nhanh thời gian
  bool isLocked = myTestCar.update(25.0); // Kiểm tra lại

  if (isLocked) {
    std::cout << " -> SUCCESS: Car locked correctly using MockClock!\n";
  } else {
    std::cout << " -> FAILURE: Logic did not work.\n";
  }

  return 0;
}

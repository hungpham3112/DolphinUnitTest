#ifndef AUTO_LOCK_SYSTEM_H
#define AUTO_LOCK_SYSTEM_H

#include "clock_interface.h"
#include <chrono>
#include <cstdint>

class RealClock : public IClock {
public:
  uint32_t get_time() const override {
    using namespace std::chrono;
    // Gọi System Call: Tốn chi phí Context Switch và phụ thuộc thời gian thực
    auto now = system_clock::now();
    auto duration = now.time_since_epoch();
    return static_cast<uint32_t>(duration_cast<milliseconds>(duration).count());
  }
};

class BadAutoLockSystem {
public:
  // VẤN ĐỀ 2: Constructor tự khởi tạo dependency bên trong.
  // Không có "khe hở" (Seam) nào để người ngoài can thiệp/thay thế cái đồng hồ
  // này.
  BadAutoLockSystem() {
    // RealClock được khởi tạo ngầm định ở đây
  }
  bool update(float speed) {
    // Logic: Khóa cửa nếu chạy > 20km/h trong 5 giây
    if (speed > 20.0) {
      if (time_ == 0)
        time_ = clock.get_time();

      // LOGIC KHÓ TEST:
      // Vì 'clock' là RealClock, muốn dòng này trả về true,
      // bạn buộc phải chờ 5000ms thật sự trôi qua bên ngoài vũ trụ.
      if (clock.get_time() - time_ > 5000)
        return true;
    } else {
      time_ = 0;
    }
    return false;
  }

private:
  uint32_t time_{0};
  // VẤN ĐỀ 1: Khai báo trực tiếp Class cụ thể (Concrete Class)
  // Memory Layout: Object RealClock nằm dính liền trong BadAutoLockSystem.
  RealClock clock;
};

class AutoLockSystem {
public:
  explicit AutoLockSystem(IClock &clock);
  bool update(float speed);

private:
  uint32_t time_{0};
  IClock &clock_;
};

#endif // AUTO_LOCK_SYSTEM_H

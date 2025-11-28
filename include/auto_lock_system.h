#ifndef AUTO_LOCK_SYSTEM_H
#define AUTO_LOCK_SYSTEM_H

#include "clock_interface.h"
#include <cstdint>
class AutoLockSystem
{
  public:
    AutoLockSystem(IClock &clock);
    bool update(float speed);

  private:
    uint32_t time_{0};
    IClock &clock_;
};

#endif // AUTO_LOCK_SYSTEM_H

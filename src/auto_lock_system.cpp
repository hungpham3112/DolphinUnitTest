#include "auto_lock_system.h"

AutoLockSystem::AutoLockSystem(IClock &clock) : clock_(clock) {};

bool AutoLockSystem::update(float speed) {
  if (speed > 20.0) {
    if (time_ == 0) {
      time_ = clock_.get_time();
    }

    if (clock_.get_time() - time_ > 5000) {
      return true;
    }

  } else {
    time_ = 0;
  }

  return false;
}

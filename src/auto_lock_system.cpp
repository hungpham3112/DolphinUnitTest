#include "auto_lock_system.h"
#include <chrono>
#include <fstream>

AutoLockSystem::AutoLockSystem(IClock &clock) : clock_(clock) {};

bool AutoLockSystem::update(float speed)
{
    if (speed > 20.0)
    {
        if (time_ == 0)
        {
            time_ = clock_.get_time();
        }
        else
        {
            if (clock_.get_time() - time_ > 5000)
            {
                return true;
            }
            return false;
        }
    }
    else
    {
        time_ = 0;
        return false;
    }

    return false;
}

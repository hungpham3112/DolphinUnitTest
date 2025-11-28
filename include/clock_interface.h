#ifndef CLOCK_INTERFACE_H
#define CLOCK_INTERFACE_H

#include <cstdint>
#include <time.h>

class IClock
{
  public:
    virtual ~IClock() = default;
    virtual uint32_t get_time() const = 0;
};

#endif // CLOCK_INTERFACE_H

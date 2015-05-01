#include "TxJoystick.h"

#ifndef CHANNEL_h
#define CHANNEL_h

class Channel {
  public:
    virtual void read() = 0;
    virtual int getPulse() = 0;
};

#endif

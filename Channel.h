#include "TxJoystick.h"

#ifndef CHANNEL_h
#define CHANNEL_h

/**
 * Channel.h
 *
 * Represents a channel interface
 *
 * Every channel needs to implement a read method which is called in the loop
 * and a getPulse method to return the pulse length to be written.
 *
 * @author Chris Landa
 */
class Channel {
  public:
    virtual void read() = 0;
    virtual int getPulse() = 0;
};

#endif

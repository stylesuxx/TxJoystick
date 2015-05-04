#ifndef PPM_h
#define PPM_h
#include <StandardCplusplus.h>
#include <vector>

#include "Channel.h"

/**
 * PPM.h
 */
class PPM {
  public:
    /**
     * @param pinOut     Output pin for the PPM signal
     * @param channels   Pointer to a list of pointers to the active channels
     */
    PPM(int pin, std::vector<Channel *>channels);

    /**
     * Write the PPM signal to the output pin
     */
    void write();

  private:
    void writePulse(int length);

    int _pin;
    std::vector<Channel *>_channels;
};

#endif

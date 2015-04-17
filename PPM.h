#ifndef PPM_h
#define PPM_h
#include <StandardCplusplus.h>
#include <vector>

#include "Channel.h"

/**
 * PPM.h
 * 
 * @author Chris Landa
 */
class PPM {
  public:
    /**
     * @param pinOut     Output pin for the PPM signal
     * @param channels   Pointer to a list of pointers to the single active channels
     * @param nrChannels The number of channels the transmitter supports. If this
     *                   is higher than the number of active channels, the remaining
     *                   channels are written with the minimal pulse length.
     */
    PPM(int pinOut, std::vector<Channel>* channels, int nrChannels);

    /**
     * Write the PPM signal to the output pin
     */
    void write();

  private:
    void writePulse(int length);

    int _pinOut, _nrChannels;
    std::vector<Channel>* _channels;
};

#endif

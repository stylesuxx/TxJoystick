#ifndef PPM_h
#define PPM_h
#include "Channel.h"

/**
 * PPM.h
 *
 * Represents a PPM signal 
 * 
 * @author Chris Landa
 * @version 1.0 12.08.2012
 */
class PPM{
  public:
    /**
     * Represents a PPM signal
     * 
     * @param pinOut Output pin for the PPM signal
     */
    PPM(int pinOut);
    
    /**
     * Write the PPM signal
     * 
     * @param channels The input channels to write
     */
    void write(Channel * channels[]);
    
  private:
    /**
     * Write a single PPM pulse
     */
    void writePulse(int length);
    
    /** The PPM output pin */
    int _pinOut;
};

#endif
#include "TxJoystick.h"
#include "Config.h"
#include "Channel.h"

#ifndef AUX_h
#define AUX_h

/**
 * Aux.h
 *
 * Represents an AUX channel
 *
 * An AUX channel may either be an analog input with 3 states or a digital input
 * attached to a switch with on off state or to a button with 2 or 3 states.
 *
 * @author Chris Landa
 */
class Aux: public Channel {
  public:
    /**
     * Aux channel
     *
     * @param pin    Aux pin
     * @param mode   Aux modes:
     *               DIGITAL_ONOFF | DIGITAL_TRI | SWITCH_ONOFF | SWITCH_TRI
     */
    Aux(int pin, auxMode mode);

    /* Read the input and trimmers if any and store them to local variables */
    void read();

    /**
     * @return Pulse length
     */
    int getPulse();

  private:
    int _pin;
    int _state;
    int _last;
    int _pause;
    auxMode _mode;
};

#endif

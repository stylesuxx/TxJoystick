#include "TxJoystick.h"
#include "Config.h"
#include "Channel.h"

#ifndef STEERING_h
#define STEERING_h

/**
 * Steering.h
 *
 * Represents a steering channel
 *
 * A steering channel has to be attached to an analog pin. There are two types
 * of steering channels, once that are trimmable and the once that are not.
 *
 * @author Chris Landa
 */
class Steering: public Channel {
  public:
    /**
     * Steering channel without trims
     *
     * @param pin    Steering pin
     * @param invert Invert the read input value
     */
    Steering(int pin, bool invert);

    /**
     * Steering channel wit trims
     *
     * @param pin         Steering pin
     * @param invert      Invert the read input value
     * @param pinTrimUp   Trim + pin
     * @param pinTrimDown Trim - pin
     * @param trimSave    The address at which the trim value is saved to the
     *                    EEPROM to be accessible after reboot.
     */
    Steering(int pin, bool invert, int pinTrimUp, int pinTrimDown, int trimSave);

    /* Read the input and trimmers if any and store them to local variables */
    void read();

    /**
     * @return Pulse length
     */
    int getPulse();

    /**
     * Set the center of the input when the controller is switched on.
     * This value is than used to determine if the min movement threshold has
     * been reached.
     */
    void setCenter();

    /**
     * Adjust the minimum and maximum read values of the analog inputs
     *
     * @param min The minimum value read on the analog pin
     * @param max The maxuimum value read on the analog pin
     */
    void adjust(int min, int max);

  private:
    void readTrims();
    bool checkTrimState(int currentValue, int *lastValue);

    int _pin;
    int _value;

    bool _isInverted;

    bool _isTrimmable;
    int _pinTrimUp;
    int _pinTrimDown;
    int _trimSave;
    int _trimValue;
    int _lastUp;
    int _lastDown;

    bool _isCentered;
    int _center;

    bool _isAdjustable;
    int _min;
    int _max;

    int _pulse;
};

#endif

#ifndef Channel_h
#define Channel_h
#include "Arduino.h"
#include "Input.h"

/** 
 * Channel.h
 * 
 * Represents a R/C channel
 * Input source may be a plain digital input or analog input with and without trims.
 *   
 * @author Chris Landa
 */
class Channel {
  public:
    /**
     * @param pinIn Digital input pin
     * @param mode  Digital channel mode can be ONOFF | TRI
     */
    Channel(int pinIn, bool invert, int mode);

    /**
     * @param pinIn  Analog input pin
     * @param invert Invert the input of this Channel
     */
    Channel(int pinIn, bool invert);

    /**
     * @param pinIn       Analog input pin
     * @param invert      Invert the input of this Channel
     * @param pinTrimUp   Digital input pin for up trimmer
     * @param pinTrimDown Digital input pin for down trimmer
     * @param pTrimSave   At which position to save the trim v
     */
    Channel(int pinIn, bool invert, int pinTrimUp, int pinTrimDown, int pTrimSave);

    /* Read the input and trimmers if any */
    void read();

    /**
     * @return Last read value
     */
    int getValue();

    /**
     * @param min Minimal possible analog value
     * @param max Maximal possible analog value
     */
    void adjust(int min, int max);

  private:
    /* Read and update the trimmer values */
    void readTrim();

    /**
     * @return True if the trimmer value has changed
     */
    bool checkChanged(int currentValue, int *lastValue);

    int _pinIn;
    int _pinTrimUp;
    int _pinTrimDown;
    int _mode;
    int _active;
    int _value;
    int _trimValue;
    int _lastDown;
    int _lastUp;
    int _pTrimSave;
    bool _trim;
    bool _invert;

    Input *_pInput;
};

#endif

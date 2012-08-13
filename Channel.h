#ifndef Channel_h
#define Channel_h
#include "Arduino.h"
#include "Input.h"

/** 
 * Channel.h
 * 
 * Represents a R/C channel, Input may be from analog input with and without trims or plain digital input
 *   
 * @author Chris Landa
 * @version 1.0 12.08.2012
 */
class Channel{
  public:
    /**
     * Digital input channel
     * 
     * @param pinIn Digital input pin
     * @param mode Digital channel mode can be ONOFF | TRI
     * @param active Channel may be HIGH | LOW active
     */
    Channel(int pinIn, int mode);

    /**
     * Analog input channel without Trims
     * 
     * @param pinIn Analog input pin
     * @param invert Invert the input of this Channel
     */
    Channel(int pinIn, bool invert);
    
    /**
     * Analog input channel with Trims
     * 
     * @param pinIn Analog input pin
     * @param invert Invert the input of this Channel
     * @param pinTrimUp Digital input pin for up trimmer
     * @param pinTrimDown Digital input pin for down trimmer
     */
    Channel(int pinIn, bool invert, int pinTrimUp, int pinTrimDown, int pTrimSave);
    
    /**
     * Reads the current input pin value and saves it 
     */
    void read();
    
    /**
     * Returns the saved input pin value
     * 
     * @return Saved input pin value of previous read
     */
    int getValue();
    
    /**
     * Better adjustment for analog input pins, set max and min possible value
     * 
     * @param min Minimal possible analog value
     * @param max Maximal possible analog value
     */
    void adjust(int min, int max);
    
  private:
    /**
     * Read the trimmers if the channel has any
     */
    void readTrim();
    
    /**
     * Check if the trimmer value has changed
     * 
     * @return If the trimmer value has changed
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
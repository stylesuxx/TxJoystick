#ifndef Input_h
#define Input_h

/**
 * Input.h
 * 
 * Abstract and deriving classes for analog and digital input
 * 
 * @author Chris Landa
 * @version 1.0 12.08.2012
 */
class Input{
  public:
    /**
     * Read value from input pin
     */
    virtual int read() = 0;
    
    /**
     * Adjust range for input
     */
    virtual void adjust(int adjustMin, int adjustMax){};
};

/**
 * Represents an analog input
 */
class Analog : public Input{
  public:
    /**
     * Analog input
     * 
     * @param pinIn Input pin
     * @param invert Invert the input
     */
    Analog(int pinIn, bool invert);
    
    /**
     * Read value from analog input pin
     * 
     * @return Returns the value read from input pin
     */
    int read();
    
    /**
     * Ajust range for analog input pins
     * 
     * @param adjustMin Minimum analog input value
     * @param adjustMax Maximum analog input value
     */
    void adjust(int adjustMin, int adjustMax);
    
  private:
    int _pinIn;
    int _value;
    bool _invert;
    bool _adjust;
    int _adjustMin;
    int _adjustMax;
};


/**
 * Represents a diital input
 */
class Digital : public Input{
  public:
    /**
     * Digital input
     * 
     * @param pinIn Input pin
     * @param mode Input mode: ONOFF | TRI
     */
    Digital(int pinIn, int mode);

    /**
     * Read value from digital input pin
     * 
     * @return Returns the value read from input pin
     */ 
    int read();
    
  private:
    /**
     * Convert button state to PPM value
     */
    void stateToValue();
    
    int _pinIn;
    int _mode;
    int _value;
    int _state;
    int _lastRead;
};

#endif
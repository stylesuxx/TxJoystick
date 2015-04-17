#ifndef Input_h
#define Input_h

/**
 * Input.h
 * 
 * Abstract and deriving classes for analog and digital inputs
 * 
 * @author Chris Landa
 */
class Input{
  public:
    /* Read value from input pin */
    virtual int read() = 0;
    
    /* Adjust range for input */
    virtual void adjust(int adjustMin, int adjustMax){};
};

/* Analog input */
class Analog : public Input{
  public:
    /**
     * @param pinIn Input pin
     * @param invert Invert the input
     */
    Analog(int pinIn, bool invert);
    
    /**
     * @return Returns the value read from input pin
     */
    int read();
    
    /**
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

/* Digital input */
class Digital : public Input{
  public:
    /**
     * @param pinIn Input pin
     * @param mode Input mode: ONOFF | TRI
     */
    Digital(int pinIn, int mode);

    /**
     * @return Returns the value read from input pin
     */ 
    int read();
    
  private:
    void stateToValue();
    
    int _pinIn;
    int _mode;
    int _value;
    int _state;
    int _lastRead;
};

#endif

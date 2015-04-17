#include "Arduino.h"
#include "Config.h"
#include "avr/eeprom.h"
#include "Channel.h"
#include "Input.h"

/** 
 * Channel.cpp
 * 
 * Represents a R/C channel
 * Input source may be a plain digital input or analog input with and without trims.
 *   
 * @author Chris Landa
 */
Channel::Channel(int pinIn, int mode) {
  _pinIn = pinIn;
  _mode = mode;

  _value = MINPULSE;
  _trim = false;

  _pInput = new Digital(_pinIn, _mode);
}

Channel::Channel(int pinIn, bool invert) {
  _pinIn = pinIn;
  _invert = invert;

  _mode = ANALOG;
  _active = ANALOG;
  _value = MINPULSE;
  _trim = false;

  _pInput = new Analog(_pinIn, _invert);
}

Channel::Channel(int pinIn, bool invert, int pinTrimUp, int pinTrimDown, int pTrimSave) {
  _pinIn = pinIn;
  _invert = invert;
  _pinTrimUp = pinTrimUp;
  _pinTrimDown = pinTrimDown;
  _pTrimSave = pTrimSave;

  _mode = ANALOG;
  _active = HIGH;
  _value = MINPULSE;
   eeprom_read_block((void*)&_trimValue, (void*)_pTrimSave, sizeof(_trimValue));

  _lastDown = -1;
  _lastUp = -1;
  _trim = true;

  _pInput = new Analog(_pinIn, _invert);
  pinMode(_pinTrimDown, INPUT);
  digitalWrite(_pinTrimDown, ACTIVE);
  pinMode(_pinTrimUp, INPUT);
  digitalWrite(_pinTrimUp, ACTIVE);  
}

void Channel::read() {
  _value = _pInput->read();

  if(_trim) readTrim();
}

int Channel::getValue() {
  int value = _value;
  if(_trim) value += _trimValue;

  /* Sanitize the value to be within the min and max pulse length */
  if(value < MINPULSE) value = MINPULSE;
  if(value > MAXPULSE) value = MAXPULSE;

  return value;
}

void Channel::adjust(int min, int max) {
  _pInput->adjust(min, max);
}

void Channel::readTrim() {
  int pinDownValue = digitalRead(_pinTrimDown);
  int pinUpValue = digitalRead(_pinTrimUp);

  /* Update the eeprom if the trim value has changed */
  if(checkChanged(pinUpValue, &_lastUp) || checkChanged(pinDownValue, &_lastDown)) {
    eeprom_write_block(&_trimValue, (void*)_pTrimSave, sizeof(_trimValue));  
  }
}

bool Channel::checkChanged(int currentValue, int *lastValue) {
  bool changed = false;

  if(*lastValue != currentValue) {
      *lastValue = currentValue;

      switch(_active){
	case HIGH: {
	  if(currentValue == LOW) {
	    _trimValue = _trimValue - 1;
	    changed = true; 
	  } break;
	}
	case LOW: {
	  if(currentValue == HIGH) {
	    _trimValue = _trimValue - 1;
	    changed = true;
	  } break;
	}
	default: break;
      }
  }

  return changed;
}

#include "Arduino.h"
#include "Config.h"
#include "Input.h"

/**
 * Digital.cpp
 *
 * Represents a digital input 
 * 
 * @author Chris Landa
 * @version 1.0 12.08.2012
 */
Digital::Digital(int pinIn, int mode){
  _pinIn = pinIn;
  _mode = mode;
  _value = MINPULSE;
  _state = 0;
  _lastRead = 2;
  
  pinMode(_pinIn, INPUT);
  digitalWrite(_pinIn, ACTIVE);
}

int Digital::read(){
  int pinValue = digitalRead(_pinIn);
  bool changed = false;
  
  if(_lastRead != pinValue){
    _lastRead = pinValue;
    
    switch(ACTIVE){
      case HIGH:{
	if(pinValue == LOW){
	  changed = true;
	}
	break;
      }
      case LOW:{
	if(pinValue == HIGH){
	  changed = true;
	}
	break;
      }
      default: break;
    }
    
    if(changed){
      _state = ++_state % 3;
      if(_mode == ONOFF && _state == 1){
	_state++;
      }
    }
  }
  
  stateToValue();

  return _value;
}

void Digital::stateToValue(){
  switch(_state){
    case 0: _value = MINPULSE; break;
    case 1: _value = MINPULSE + ((MAXPULSE - MINPULSE)/2); break;
    case 2: _value = MAXPULSE; break;
    default: break;
  }
}
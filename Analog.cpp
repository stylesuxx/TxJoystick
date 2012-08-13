#include "Arduino.h"
#include "Config.h"
#include "Input.h"

/** 
 * Analog.cpp
 * 
 * Represents an analog input
 * 
 * @author Chris Landa
 * @version 1.0 12.08.2012
 */
Analog::Analog(int pinIn, bool invert){
  _pinIn = pinIn;
  _invert = invert;
  _value = MINPULSE;
  _adjust = false;
  _adjustMin = 0;
  _adjustMax = 0;
  
  digitalWrite(_pinIn, HIGH);
}

int Analog::read(){
  int rawValue = analogRead(_pinIn);
  
  if(_invert){
    _value = map(rawValue, 0, 1023, MAXPULSE, MINPULSE);
    if(_adjust){
      _value = map(_value, _adjustMin, _adjustMax, MINPULSE, MAXPULSE);
    }
  }
  else{
    _value = map(rawValue, 0, 1023, MINPULSE, MAXPULSE);
    if(_adjust){
      _value = map(_value, _adjustMin, _adjustMax, MINPULSE, MAXPULSE);
    }
  }
  
  return _value;
}

void Analog::adjust(int adjustMin, int adjustMax){
  _adjust = true;
  _adjustMin = adjustMin;
  _adjustMax = adjustMax;
}
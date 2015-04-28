#include "Arduino.h"
#include "Config.h"
#include "Input.h"

/**
 * Analog.cpp
 *
 * @author Chris Landa
 */
Analog::Analog(int pinIn, bool invert) {
  _pinIn = pinIn;
  _invert = invert;

  _value = MINPULSE;

  _adjust = false;
  _adjustMin = 0;
  _adjustMax = 0;
}

int Analog::read() {
  _value = analogRead(_pinIn);

  if(_adjust) {
    _value = map(_value, _adjustMin, _adjustMax, MINPULSE, MAXPULSE);
  }

  if(_invert) {
    _value = map(_value, MINPULSE, MAXPULSE, MAXPULSE, MINPULSE);
  }

  return _value;
}

void Analog::adjust(int adjustMin, int adjustMax) {
  _adjust = true;
  _adjustMin = adjustMin;
  _adjustMax = adjustMax;
}

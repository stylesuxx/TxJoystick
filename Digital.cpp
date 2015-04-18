#include "Arduino.h"
#include "Config.h"
#include "Input.h"

/**
 * Digital.cpp
 *
 * @author Chris Landa
 */
Digital::Digital(int pinIn, int mode) {
  _pinIn = pinIn;
  _mode = mode;
  _value = MINPULSE;
  _state = 0;
  _lastRead = 2;

  pinMode(_pinIn, INPUT);
  digitalWrite(_pinIn, ACTIVE);
}

int Digital::read() {
  int pinValue = digitalRead(_pinIn);
  bool changed = false;

  if(_lastRead != pinValue) {
    _lastRead = pinValue;

    if((ACTIVE == HIGH && pinValue == LOW) ||
       (ACTIVE == LOW && pinValue == HIGH)) {
      changed = true;
    }

    if(changed) {
      _state = ++_state % 3;
      if(_mode == ONOFF && _state == 1) {
        _state++;
      }

      if(BUZZER) {
        for(int i = 0; i < _state + 1; ++i) {
          digitalWrite(BUZZER_PIN, HIGH);
          delay(50);
          digitalWrite(BUZZER_PIN, LOW);
          delay(50);
        }
      }
    }
  }

  stateToValue();

  return _value;
}

/* Convert button state to PPM value */
void Digital::stateToValue() {
  switch(_state){
    case 0: _value = MINPULSE; break;
    case 1: _value = MINPULSE + ((MAXPULSE - MINPULSE)/2); break;
    case 2: _value = MAXPULSE; break;
    default: break;
  }
}

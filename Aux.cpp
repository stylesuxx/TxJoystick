#include "Aux.h"

Aux::Aux(int pin, auxMode mode) {
  _pin = pin;
  _mode = mode;
  _state = 0;
  _last = 2;
  _pause = 0;

  _pulse = MINPULSE;

  if(ENABLE_PULLUPS) pinMode(_pin, INPUT_PULLUP);
  else pinMode(_pin, INPUT);
}

void Aux::read() {
  if(_pause > 0) --_pause;

  switch(_mode) {
    case DIGITAL_ONOFF:
    case DIGITAL_TRI: {
      int value = digitalRead(_pin);
      if(_last != value && _pause == 0) {
        _last = value;

        if((ACTIVE == HIGH && value == HIGH) ||
           (ACTIVE == LOW  && value == LOW)) {

          _state = ++_state % 3;

          /* Skip middle position if in ONOFF mode */
          if(_mode == DIGITAL_ONOFF && _state == 1) {
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

          _pause = 500;
        }
      }
    } break;

    /**
     * Mechanical on/off switch with two positions. May either be attached to a
     * digital or analog pin.
     */
    case SWITCH_ONOFF: {
      int value = digitalRead(_pin);
      if((ACTIVE == HIGH && value == HIGH) ||
         (ACTIVE == LOW  && value == LOW)) {

        _state = 2;
      }
      else {
        _state = 0;
      }
    } break;

    case SWITCH_TRI: {
      // TODO
    } break;

    default: {
      _state = 0;
    }
  }

  switch(_state){
    case 0: _pulse = MINPULSE; break;
    case 1: _pulse = MINPULSE + ((MAXPULSE - MINPULSE) / 2); break;
    case 2: _pulse = MAXPULSE; break;
    default: break;
  }
}

int Aux::getPulse() {
  return _pulse;
}

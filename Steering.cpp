#include "Steering.h"
#include "avr/eeprom.h"

/**
 * Analog.cpp
 */
Steering::Steering(int pin, bool invert) {
  _pin = pin;
  _isInverted = invert;

  _isTrimmable = false;
  _isCentered = false;
  _isAdjustable = false;

  _value = 0;

  _pulse = MINPULSE;
}

Steering::Steering(int pin, bool invert, int pinTrimUp, int pinTrimDown, int trimSave) {
  _pin = pin;
  _pinTrimUp = pinTrimUp;
  _pinTrimDown = pinTrimDown;
  _trimSave = trimSave;
  eeprom_read_block((void*)&_trimValue, (void*)_trimSave, sizeof(_trimValue));
  _isInverted = invert;

  _isTrimmable = true;
  _isCentered = false;
  _isAdjustable = false;

  _value = 0;

  _pulse = MINPULSE;

  if(ENABLE_PULLUPS) {
    pinMode(_pinTrimDown, INPUT_PULLUP);
    pinMode(_pinTrimUp, INPUT_PULLUP);
  }
  else {
    pinMode(_pinTrimDown, INPUT);
    pinMode(_pinTrimUp, INPUT);
  }
}

void Steering::read() {
  _value = analogRead(_pin);

  if(_isTrimmable) readTrims();

  int current = _value;
  if(_isCentered) {
    if(current > (_center + MIN_MOVEMENT)) {
      current = current - MIN_MOVEMENT;
    }
    else if(current < (_center - MIN_MOVEMENT)) {
      current = current + MIN_MOVEMENT;
    }
    else {
      current = _center;
    }
  }

  if(_isAdjustable) {
    current = map(current, _min, _max, MINPULSE, MAXPULSE);
  }
  else {
    current = map(current, 0, 1023, MINPULSE, MAXPULSE);
  }

  if(_isInverted) {
    current = map(current, MINPULSE, MAXPULSE, MAXPULSE, MINPULSE);
  }

  if(_isTrimmable) {
    current += _trimValue;
  }

  if(current < MINPULSE) current = MINPULSE;
  if(current > MAXPULSE) current = MAXPULSE;

  _pulse = current;
}

int Steering::getPulse() {
  return _pulse;
}

void Steering::adjust(int min, int max) {
  _min = min;
  _max = max;

  _isAdjustable = true;
}

void Steering::readTrims() {
  int pinDownValue = digitalRead(_pinTrimDown);
  int pinUpValue = digitalRead(_pinTrimUp);

  if(checkTrimState(pinUpValue, &_lastUp)) {
    _trimValue += 1;

    eeprom_write_block(&_trimValue, (void*)_trimSave, sizeof(_trimValue));
  }

  if(checkTrimState(pinDownValue, &_lastDown)) {
    _trimValue -= 1;

    eeprom_write_block(&_trimValue, (void*)_trimSave, sizeof(_trimValue));
  }
}

void Steering::setCenter() {
  _center = analogRead(_pin);
  _isCentered = true;
}

bool Steering::checkTrimState(int currentValue, int *lastValue) {
  bool changed = false;

  if(*lastValue != currentValue) {
    *lastValue = currentValue;

    if((ACTIVE == HIGH && currentValue == HIGH) ||
       (ACTIVE == LOW  && currentValue == LOW)) {
      changed = true;

      if(BUZZER) {
        digitalWrite(BUZZER_PIN, HIGH);
        delay(50);
        digitalWrite(BUZZER_PIN, LOW);
        delay(10);
      }
    }
  }

  return changed;
}
#include "Config.h"
#include "Channel.h"
#include "PPM.h"

PPM::PPM(int pinOut, std::vector<Channel>* channels) {
  _pinOut = pinOut;
  _channels = channels;

  pinMode(_pinOut, OUTPUT);
}

void PPM::write() {
  /* Write the active channels */
  for (std::vector<Channel>::iterator ch = _channels->begin() ; ch != _channels->end(); ++ch) {
    writePulse(ch->getValue());

    if(DEBUG) {
      Serial.print(ch->getValue());
      Serial.print(" ");
    }
  }
  if(DEBUG) Serial.println("");

  /* Pad the remaining channels with minimum length pulses */
  for(int i = _channels->size(); i < CHANNELS; ++i) {
    writePulse(MINPULSE);
  }

  /* Write the synch pulse */
  writePulse(SYNCPULSE);
}

void PPM::writePulse(int length) {
  digitalWrite(_pinOut, LOW);
  delayMicroseconds(STOPULSE);
  digitalWrite(_pinOut, HIGH);
  delayMicroseconds(length);
  digitalWrite(_pinOut, LOW);
}

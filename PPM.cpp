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

  /**
   * Synch pulse
   * NOTE: Since delayMicroseconds only works reliably from 3ms up this is not implemened with writePulse(0)
   */
  digitalWrite(_pinOut, LOW);
  delayMicroseconds(SYNCPULSE);
  digitalWrite(_pinOut, HIGH);
}

void PPM::writePulse(int length) {
  digitalWrite(_pinOut, LOW);
  delayMicroseconds(STOPULSE);
  digitalWrite(_pinOut, HIGH);
  delayMicroseconds(length);
}

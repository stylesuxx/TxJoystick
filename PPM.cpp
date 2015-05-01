#include "Config.h"
#include "Channel.h"
#include "PPM.h"

PPM::PPM(int pin, std::vector<Channel *>channels) {
  _pin = pin;
  _channels = channels;

  pinMode(_pin, OUTPUT);
}

void PPM::write() {
  /* Write the active channels */
  std::vector<Channel *>::iterator iter = _channels.begin();
  for (iter; iter != _channels.end(); ++iter) {
    writePulse((*iter)->getPulse());
  }

  /* Pad the remaining channels with minimum length pulses */
  for(int i = _channels.size(); i < CHANNELS; ++i) {
    writePulse(MINPULSE);
  }

  /* Write the synch pulse */
  writePulse(SYNCPULSE);
}

void PPM::writePulse(int length) {
  digitalWrite(_pin, LOW);
  delayMicroseconds(STOPULSE);
  digitalWrite(_pin, HIGH);
  delayMicroseconds(length);
  digitalWrite(_pin, LOW);
}

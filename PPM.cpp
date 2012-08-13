#include "Config.h"
#include "PPM.h"

/**
 * PPM.cpp
 *
 * Represents a PPM signal 
 * 
 * @author Chris Landa
 * @version 1.0 12.08.2012
 */
PPM::PPM(int pinOut){
  _pinOut = pinOut;
  
  pinMode(_pinOut, OUTPUT);
}

void PPM::write(Channel * pChannels[]){
  int length;
  for(int i = 0; i < CHANNELS; i++){
    length = pChannels[i]->getValue();
    writePulse(length);
  }
  
  // Synch pulse
  // Since delayMicroseconds only works reliably from 3ms up this is not implemened with writePulse(0)
  digitalWrite(_pinOut, LOW);
  delayMicroseconds(STOPULSE);
  digitalWrite(_pinOut, HIGH);
}

void PPM::writePulse(int length){
  digitalWrite(_pinOut, LOW);
  delayMicroseconds(STOPULSE);
  digitalWrite(_pinOut, HIGH);
  delayMicroseconds(length);      	
}
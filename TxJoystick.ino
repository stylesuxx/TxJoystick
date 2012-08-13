#include "Config.h"
#include "Channel.h"
#include "PPM.h"

/** 
 * TxJoystick.ino
 * 
 * An Arduino based R/C Transmitter for use with a Joystick, Joypad or any other input device
 * 
 * @author Chris Landa
 * @version 1.0 12.08.2012
 */

Channel throttle(A0, true);
Channel yaw(A1, false, 6, 7, 1);
Channel pitch(A2, true, 4, 5, 10);
Channel roll(A3, false, 2, 3, 20);
  
Channel aux1(8, TRI);
Channel aux2(0, TRI);
Channel aux3(0, ONOFF);
Channel aux4(0, ONOFF);

Channel *pChannels[] = {
  &throttle,
  &roll,
  &pitch,
  &yaw,
  &aux1,
  &aux2,
  &aux3,
  &aux4
};

PPM PPM(10);

ISR(TIMER1_COMPA_vect){
    PPM.write(pChannels);
}

void setup(){  
  // Set Timer Counter Controll Register for Timer1
  TCCR1A = B00110001;	// Compare register B used in mode '3'
  TCCR1B = B00010010;	// WGM13 and CS11 set to 1
  TCCR1C = B00000000;	// All set to 0

  TIMSK1 = B00000010;	// Interrupt on compare B
  OCR1A = 22500;	// 22,5mS PPM output refresh

  // Analog input adjustments - those are the values that really can be reached with the analog inputs
  throttle.adjust(750, 1590);  // Throttle adjust
  yaw.adjust(1050, 1620);      // Yaw adjust
  pitch.adjust(800, 1510);     // Pitch adjust
  roll.adjust(900, 1550);      // Roll adjust

  if(DEBUG){
    Serial.begin(9600);
    Serial.println("Debug Mode:");
  }
}

void loop(){ 
  for(int i = 0; i < CHANNELS; i++){
    pChannels[i]->read();
  }
}

#include <StandardCplusplus.h>
#include <vector>
#include <iterator>

#include "Config.h"
#include "Channel.h"
#include "PPM.h"

/**
 * An Arduino based R/C Transmitter for use with a Joystick, Joypad or any other input device
 *
 * Default pinouts:
 *
 * A0: Throttle
 * A1: Yaw
 * A2: Pitch
 * A3: Roll
 *  8: Aux 1
 *
 *  2: Roll  +
 *  3: Roll  -
 *  4: Pitch +
 *  5: Pitch -
 *  6: Yaw   +
 *  7: Yaw   -
 *
 * 10: PPM out
 *
 * @author Chris Landa
 */

/* The number of channels your transmitter supports */
int nrChannels = 8;

/**
 * Min and max values for the analog inputs
 *
 * To get this values you have to find the min and max values read from the analog input.
 * Move the stick to its maximum positions and note the minimum and maximum values you read
 * from the analog input.
 */
int throttleMin = 750;
int throttleMax = 1590;

int yawMin = 1050;
int yawMax = 1620;

int pitchMin = 800;
int pitchMax = 1510;

int rollMin = 900;
int rollMax = 1550;

/* Channels 1-4 in order they are listed */
Channel throttle(A0, true);
Channel yaw(A1, false, 6, 7, 1);
Channel pitch(A2, true, 4, 5, 10);
Channel roll(A3, false, 2, 3, 20);

/**
 * Feel free to add more AUX channels here but do not forget
 * to push them on the vector in the setup method.
 */
Channel aux1(8, TRI);
//Channel aux2(0, TRI);
//Channel aux3(0, ONOFF);
//Channel aux4(0, ONOFF);

int ppmPin = 10;

std::vector<Channel> channels;
PPM* ppm = NULL;

/* Interrupt service routine which is responsible to write the PPM pulse */
ISR(TIMER1_COMPA_vect) {
  if(ppm) ppm->write();
}

void setup() {
  channels.push_back(throttle);
  channels.push_back(yaw);
  channels.push_back(pitch);
  channels.push_back(roll);
  channels.push_back(aux1);
  /* Push additional channels here */
  ppm = new PPM(ppmPin, channels, nrChannels);

  // Set Timer Counter Controll Register for Timer1
  TCCR1A = B00110001;	// Compare register B used in mode '3'
  TCCR1B = B00010010;	// WGM13 and CS11 set to 1
  TCCR1C = B00000000;	// All set to 0

  TIMSK1 = B00000010;	// Interrupt on compare B
  OCR1A = 22500;	// 22,5mS PPM output refresh

  throttle.adjust(throttleMin, throttleMax);
  yaw.adjust(yawMin, yawMax);
  pitch.adjust(pitchMin, pitchMax);
  roll.adjust(rollMin, rollMax);

  /* If debug mode is enabled we configure the serial port to print debugging messages */
  if(DEBUG) {
    Serial.begin(115200);
    Serial.println("Debug Mode:");
  }
}

void loop() {
  for (std::vector<Channel>::iterator ch = channels.begin() ; ch != channels.end(); ++ch) {
    ch->read();
  }
}

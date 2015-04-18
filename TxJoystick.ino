#include <StandardCplusplus.h>
#include <vector>
#include <iterator>

#include "avr/eeprom.h"
#include "Config.h"
#include "Channel.h"
#include "PPM.h"

/**
 * An Arduino based R/C Transmitter for use with a Joystick, Joypad or any other input device
 *
 * @author Chris Landa
 */

/* Channels 1-4 in order they are listed */
Channel throttle(THROTTLE_PIN, true);
Channel yaw(YAW_PIN, false, YAW_UP_PIN, YAW_DOWN_PIN, 10);
Channel pitch(PITCH_PIN, true, PITCH_UP_PIN, PITCH_DOWN_PIN, 20);
Channel roll(ROLL_PIN, false, ROLL_UP_PIN, ROLL_DOWN_PIN, 30);

/**
 * Feel free to add more AUX channels here but do not forget
 * to push them on the vector in the setup method.
 */
Channel aux1(AUX_1_PIN, false, ONOFF);
//Channel aux2(AUX_2_PIN, ONOFF);
//Channel aux3(AUX_3_PIN, TRI);
//Channel aux4(AUX_4_PIN, TRI);

int ppmPin = 10;
int buzzerPin = 12;

std::vector<Channel> channels;
PPM* ppm = NULL;

/* Interrupt service routine which is responsible to write the PPM pulse */
ISR(TIMER1_COMPA_vect) {
  if(ppm) ppm->write();
}

void setup() {
  /* Initialize EEPROM for the trims, this only needs to be done once */
  int zero = 0;
  eeprom_write_block(&zero, (void*)10, sizeof(int));
  eeprom_write_block(&zero, (void*)20, sizeof(int));
  eeprom_write_block(&zero, (void*)30, sizeof(int));

  if(BUZZER) {
    /* Beep three times to signalize that we are online */
    for(int i = 0; i < 3; ++i) {
      digitalWrite(buzzerPin, HIGH);
      delay(50);
      digitalWrite(buzzerPin, LOW);
      delay(50);
    }
  }

  throttle.adjust(THROTTLE_MIN, THROTTLE_MAX);
  yaw.adjust(YAW_MIN, YAW_MAX);
  pitch.adjust(PITCH_MIN, PITCH_MAX);
  roll.adjust(ROLL_MIN, ROLL_MAX);

  channels.push_back(throttle);
  channels.push_back(yaw);
  channels.push_back(pitch);
  channels.push_back(roll);
  channels.push_back(aux1);
  /* Push additional channels here */
  ppm = new PPM(ppmPin, &channels);

  /* Set Timer Counter Controll Register for Timer1 */
  TCCR1A = B00110001; // Compare register B used in mode '3'
  TCCR1B = B00010010; // WGM13 and CS11 set to 1
  TCCR1C = B00000000; // All set to 0
  TIMSK1 = B00000010; // Interrupt on compare B
  OCR1A = 22500;      // 22,5mS PPM output refresh

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

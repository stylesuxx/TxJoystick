#include <StandardCplusplus.h>
#include <vector>
#include <iterator>

#include "TxJoystick.h"
#include "avr/eeprom.h"
#include "Config.h"
#include "Channel.h"
#include "PPM.h"

/**
 * An Arduino based R/C Transmitter for use with a Joystick, Joypad or any other input device
 *
 * @author Chris Landa
 */

std::vector<Channel> channels;
PPM* ppm = NULL;

/* Interrupt service routine which is responsible to write the PPM pulse */
ISR(TIMER1_COMPA_vect) {
  if(ppm) ppm->write();
}

void setup() {
  /* Set Timer Counter Controll Register for Timer1 */
  TCCR1A = B00110001; // Compare register B used in mode '3'
  TCCR1B = B00010010; // WGM13 and CS11 set to 1
  TCCR1C = B00000000; // All set to 0
  TIMSK1 = B00000010; // Interrupt on compare B
  OCR1A = 22500;      // 22,5mS PPM output refresh

  if(DEBUG) {
    Serial.begin(115200);
    Serial.println("Debug Mode:");
  }

  if(INIT_EEPROM) {
    signed int zero = 0;
    eeprom_write_block(&zero, (void *)0, sizeof(signed int));
    eeprom_write_block(&zero, (void *)2, sizeof(signed int));
    eeprom_write_block(&zero, (void *)4, sizeof(signed int));
  }

  if(BUZZER) {
    /* Beep three times to signalize that we are online */
    for(int i = 0; i < 3; ++i) {
      digitalWrite(BUZZER_PIN, HIGH);
      delay(50);
      digitalWrite(BUZZER_PIN, LOW);
      delay(50);
    }
  }

  /* Channels 1-4 in order they are listed */
  Channel throttle(THROTTLE_PIN, true);
  Channel yaw(YAW_PIN, false, YAW_UP_PIN, YAW_DOWN_PIN, 0);
  Channel pitch(PITCH_PIN, true, PITCH_UP_PIN, PITCH_DOWN_PIN, 2);
  Channel roll(ROLL_PIN, false, ROLL_UP_PIN, ROLL_DOWN_PIN, 4);

  throttle.adjust(THROTTLE_MIN, THROTTLE_MAX);
  yaw.adjust(YAW_MIN, YAW_MAX);
  pitch.adjust(PITCH_MIN, PITCH_MAX);
  roll.adjust(ROLL_MIN, ROLL_MAX);

  yaw.readCenter();
  pitch.readCenter();
  roll.readCenter();

  channels.push_back(throttle);
  channels.push_back(yaw);
  channels.push_back(pitch);
  channels.push_back(roll);

  /**
   * Channels 5-8
   */
  if(AUX_1_ENABLE) {
    Channel aux1(AUX_1_PIN, false, AUX_1_MODE);
    channels.push_back(aux1);
  }
  if(AUX_2_ENABLE) {
    Channel aux2(AUX_2_PIN, false, AUX_2_MODE);
    channels.push_back(aux2);
  }
  if(AUX_3_ENABLE) {
    Channel aux3(AUX_3_PIN, false, AUX_3_MODE);
    channels.push_back(aux3);
  }
  if(AUX_4_ENABLE) {
    Channel aux4(AUX_4_PIN, false, AUX_4_MODE);
    channels.push_back(aux4);
  }

  ppm = new PPM(PPM_PIN, &channels);
}

void loop() {
  std::vector<Channel>::iterator ch = channels.begin();
  for (ch; ch != channels.end(); ++ch) {
    ch->read();
  }
}

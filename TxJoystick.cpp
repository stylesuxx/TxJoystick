#include <StandardCplusplus.h>
#include <vector>
#include <iterator>

#include "TxJoystick.h"
#include "Steering.h"
#include "Aux.h"

#include "avr/eeprom.h"
#include "Config.h"
//#include "Channel.h"
#include "PPM.h"

/**
 * An Arduino based R/C Transmitter for use with a Joystick, Joypad or any other input device
 *
 * @author Chris Landa
 */

std::vector<Channel *> channels;
PPM* ppm = NULL;
bool setupDone = false;

/* Interrupt service routine which is responsible to write the PPM pulse */
ISR(TIMER1_COMPA_vect) {
  if(setupDone) ppm->write();
}

void setup() {
  /* Set Timer Counter Controll Register for Timer1 */
  TCCR1A = B00110001; // Compare register B used in mode '3'
  TCCR1B = B00010010; // WGM13 and CS11 set to 1
  TCCR1C = B00000000; // All set to 0
  TIMSK1 = B00000010; // Interrupt on compare B
  //OCR1A = 22500;      // 22,5mS PPM output refresh
  OCR1A = 20000;      // 22,5mS PPM output refresh

  if(DEBUG) {
    Serial.begin(115200);
    Serial.println("Debug Mode:");
  }

  if(INIT_EEPROM) {
    signed int zero = 0;
    eeprom_write_block(&zero, (void *) THROTTLE_TRIM_SAVE, sizeof(signed int));
    eeprom_write_block(&zero, (void *) YAW_TRIM_SAVE, sizeof(signed int));
    eeprom_write_block(&zero, (void *) PITCH_TRIM_SAVE, sizeof(signed int));
    eeprom_write_block(&zero, (void *) ROLL_TRIM_SAVE, sizeof(signed int));
  }

  /* Steering channels */
  if(THROTTLE_ENABLE) {
    Steering* throttle;
    if(THROTTLE_TRIM_ENABLE) {
      throttle = new Steering(THROTTLE_PIN, THROTTLE_INVERT,
                              THROTTLE_UP_PIN, THROTTLE_DOWN_PIN,
                              THROTTLE_TRIM_SAVE);
    }
    else {
      throttle = new Steering(THROTTLE_PIN, THROTTLE_INVERT);
    }

    if(THROTTLE_ADJUST) {
      throttle->adjust(THROTTLE_MIN, THROTTLE_MAX);
    }

    if(THROTTLE_SET_CENTER) {
      throttle->setCenter();
    }

    channels.push_back(throttle);
  }

  if(YAW_ENABLE) {
    Steering* yaw;
    if(YAW_TRIM_ENABLE) {
      yaw = new Steering(YAW_PIN, YAW_INVERT,
                         YAW_UP_PIN, YAW_DOWN_PIN, YAW_TRIM_SAVE);
    }
    else {
      yaw = new Steering(YAW_PIN, YAW_INVERT);
    }

    if(YAW_ADJUST) {
      yaw->adjust(YAW_MIN, YAW_MAX);
    }

    if(YAW_SET_CENTER) {
      yaw->setCenter();
    }

    channels.push_back(yaw);
  }

  if(PITCH_ENABLE) {
    Steering* pitch;
    if(PITCH_TRIM_ENABLE) {
      pitch = new Steering(PITCH_PIN, PITCH_INVERT,
                         PITCH_UP_PIN, PITCH_DOWN_PIN, PITCH_TRIM_SAVE);
    }
    else {
      pitch = new Steering(PITCH_PIN, PITCH_INVERT);
    }

    if(PITCH_ADJUST) {
      pitch->adjust(PITCH_MIN, PITCH_MAX);
    }

    if(PITCH_SET_CENTER) {
      pitch->setCenter();
    }

    channels.push_back(pitch);
  }

  if(ROLL_ENABLE) {
    Steering* roll;
    if(ROLL_TRIM_ENABLE) {
      roll = new Steering(ROLL_PIN, ROLL_INVERT,
                         ROLL_UP_PIN, ROLL_DOWN_PIN, ROLL_TRIM_SAVE);
    }
    else {
      roll = new Steering(ROLL_PIN, ROLL_INVERT);
    }

    if(ROLL_ADJUST) {
      roll->adjust(ROLL_MIN, ROLL_MAX);
    }

    if(ROLL_SET_CENTER) {
      roll->setCenter();
    }

    channels.push_back(roll);
  }

  /**
   * Aux channels
   */
  if(AUX_1_ENABLE) {
    Aux* aux1 = new Aux(AUX_1_PIN, AUX_1_MODE);
    channels.push_back(aux1);
  }

  if(AUX_2_ENABLE) {
    Aux* aux2 = new Aux(AUX_2_PIN, AUX_2_MODE);
    channels.push_back(aux2);
  }

  if(AUX_3_ENABLE) {
    Aux* aux3 = new Aux(AUX_3_PIN, AUX_3_MODE);
    channels.push_back(aux3);
  }

  if(AUX_4_ENABLE) {
    Aux* aux4 = new Aux(AUX_4_PIN, AUX_4_MODE);
    channels.push_back(aux4);
  }

  ppm = new PPM(PPM_PIN, channels);

  if(BUZZER) {
    pinMode(BUZZER_PIN, OUTPUT);

    /* Beep three times to signalize that the controlls are ready */
    for(int i = 0; i < 3; ++i) {
      digitalWrite(BUZZER_PIN, HIGH);
      delay(50);
      digitalWrite(BUZZER_PIN, LOW);
      delay(50);
    }
  }

  setupDone = true;
}

void loop() {
  /* Read the pins of the input channels indefinetly */
  std::vector<Channel *>::iterator iter = channels.begin();
  for (iter; iter != channels.end(); ++iter) {
    (*iter)->read();

    if(DEBUG) {
      Serial.print((*iter)->getPulse());
      Serial.print(" ");
    }
  }

  if(DEBUG) Serial.println("");
}

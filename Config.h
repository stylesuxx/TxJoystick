#include "TxJoystick.h"

#ifndef CONFIG_h
#define CONFIG_h
/**
 * Configuration definitions
 *
 * @author Chris Landa
 */

/* The number of channels your transmitter supports */
#define CHANNELS 8

/**
 * Initializes the eprom for the trims with 0
 *
 * This needs to be done the first time the board is programmed or when you want
 * to reset the trims all together.
 */
#define INIT_EEPROM true

/* Pin configuration */
#define THROTTLE_PIN   A0
#define YAW_PIN        A1
#define PITCH_PIN      A2
#define ROLL_PIN       A3

#define AUX_1_PIN       8
#define AUX_2_PIN       9
#define AUX_3_PIN      11
#define AUX_4_PIN      13

#define YAW_UP_PIN      6
#define YAW_DOWN_PIN    7
#define PITCH_UP_PIN    4
#define PITCH_DOWN_PIN  5
#define ROLL_UP_PIN     2
#define ROLL_DOWN_PIN   3

#define PPM_PIN        10
#define BUZZER_PIN     12

/**
 * Min and max values for the analog inputs
 *
 * To get this values you have to find the min and max values read from the analog input.
 * Move the stick to its maximum positions and note the minimum and maximum values you read
 * from the analog input.
 */
#define THROTTLE_MIN  28
#define THROTTLE_MAX 960

#define YAW_MIN 235
#define YAW_MAX 986

#define PITCH_MIN  64
#define PITCH_MAX 910

#define ROLL_MIN  31
#define ROLL_MAX 847

#define MIN_MOVEMENT 75

/**
 * Enable your AUX here and set the possible states.
 * AUX mode may either be SWITCH if you have a mechanical switch attached, TRI
 * if you want to switch between low, mid and high with a momentary switch or
 * ONOFF if you want to switch between low and high with a momentary switch.
 */
#define AUX_1_ENABLE true
#define AUX_2_ENABLE true
#define AUX_3_ENABLE false
#define AUX_4_ENABLE false

#define AUX_1_MODE SWITCH
#define AUX_2_MODE TRI
#define AUX_3_MODE ONOFF
#define AUX_4_MODE ONOFF

/* Enable serial debugging */
#define DEBUG false

/* Enable buzzer */
 #define BUZZER true

/* High or Low active */
#define ACTIVE HIGH

/**
 * PPM pulse values
 *
 * One PPM Pulse is MINPULSE - MAXPULSE microseconds long, after each pulse
 * a stop pulse of length STOPULSE is sent. After all the channels have been
 * sent a synch pulse of length SYNCPULSE is sent.
 *
 * To adjust min and max pulse value check with a switch AUX and adjust the
 * values until min and max pulse fit perfectly.
 */
#define MAXPULSE    1679
#define MINPULSE     676
#define SYNCPULSE    800
#define STOPULSE     300

#endif

#ifndef Config_h
#define Config_h
/**
 * Common defines
 *
 * @author Chris Landa
 */

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

/* The number of channels your transmitter supports */
#define CHANNELS 8

/* Enable serial debugging */
#define DEBUG true

/* Enable buzzer */
 #define BUZZER true

/* High or Low active */
#define ACTIVE HIGH

/**
 * Input Modes
 */
#define ONOFF 0
#define TRI 1
#define ANALOG -1

/**
 * Details about the PPM Pulse
 *
 * One PPM Pulse is 700-1700 ms long, after each pulse there comes a 300ms Stop Pulse
 */
#define MAXPULSE 1700
#define MINPULSE 700
#define STOPULSE 300

#endif

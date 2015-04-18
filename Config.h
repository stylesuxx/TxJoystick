#ifndef Config_h
#define Config_h
/**
 * Configuration definitions
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

/* The number of channels your transmitter supports */
#define CHANNELS 8

/* Enable serial debugging */
#define DEBUG true

/* Enable buzzer */
 #define BUZZER true

/* High or Low active */
#define ACTIVE HIGH

/**
 * PPM pulse values
 *
 * One PPM Pulse is 700-1700 ms long, after each pulse there comes a 300ms Stop Pulse
 */
#define MAXPULSE 1700
#define MINPULSE 700
#define STOPULSE 300

/**
 * Input Modes
 */
#define ONOFF 0
#define TRI 1
#define ANALOG -1

#endif

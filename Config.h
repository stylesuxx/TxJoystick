#include "TxJoystick.h"

#ifndef CONFIG_h
#define CONFIG_h

/**
 * Set the number of channels your receiver supports. If you do not intend to
 * use all the channels, the rest will be filled with a pulse of minimum pulse
 * length.
 */
#define CHANNELS 8

/**
 * Initializes the EEPROM for the trims with 0
 *
 * This needs to be done the first time the board is programmed or when you want
 * to reset the trims all together.
 */
#define INIT_EEPROM false

/**
 * Pin configuration
 *
 * Adjust the pins to your needs. If you do not intend to use all the AUX
 * channels or trims, you can leave the values as they are - they will not be
 * used then.
 */
#define THROTTLE_PIN     A0
#define YAW_PIN          A1
#define PITCH_PIN        A2
#define ROLL_PIN         A3

#define AUX_1_PIN         8
#define AUX_2_PIN         9
#define AUX_3_PIN        11
#define AUX_4_PIN        13

#define THROTTLE_UP_PIN   2
#define THROTTLE_DOWN_PIN 3
#define YAW_UP_PIN        6
#define YAW_DOWN_PIN      7
#define PITCH_UP_PIN      4
#define PITCH_DOWN_PIN    5
#define ROLL_UP_PIN       2
#define ROLL_DOWN_PIN     3

#define PPM_PIN          10
#define BUZZER_PIN       12

/**
 * Enable the steering channels
 *
 * All four steering channels are enabled by default. If you plan to steer a car
 * you will most likely only use two of them.
 */
#define THROTTLE_ENABLE true
#define YAW_ENABLE      true
#define PITCH_ENABLE    true
#define ROLL_ENABLE     true

/**
 * Enable trims for the channels you need to trim
 */
#define THROTTLE_TRIM_ENABLE false
#define YAW_TRIM_ENABLE      true
#define PITCH_TRIM_ENABLE    true
#define ROLL_TRIM_ENABLE     true

/**
 * Invert the axes if needed
 */
#define THROTTLE_INVERT true
#define YAW_INVERT      false
#define PITCH_INVERT    true
#define ROLL_INVERT     false

/**
 * Set the center value of the steering channel when switching on the controller
 *
 * Use this setting if you want your center area to be "bigger" than just the
 * center position itself. On my 4 Axis joystick if I let go of the stick it
 * jumps back to the center, but may then be off a couple of mm and thus not in
 * the calibrated center.
 */
#define THROTTLE_SET_CENTER false
#define YAW_SET_CENTER      true
#define PITCH_SET_CENTER    true
#define ROLL_SET_CENTER     true

/**
 * The minimal movement of the axes needed to not be considered the center
 * position.
 */
#define MIN_MOVEMENT 75

/**
 * Enable channels that need adjustment. You only need this if your analog
 * readings do not fully go from 0 to 1023.
 */
#define THROTTLE_ADJUST true
#define YAW_ADJUST      true
#define PITCH_ADJUST    true
#define ROLL_ADJUST     true

/**
 * Min and max values for the analog inputs
 *
 * To get this values you have to find the min and max values read from the
 * analog input. Move the stick to its maximum positions and note the minimum
 * and maximum values you read from the analog input.
 */
#define THROTTLE_MIN  28
#define THROTTLE_MAX 960

#define YAW_MIN 235
#define YAW_MAX 986

#define PITCH_MIN  64
#define PITCH_MAX 910

#define ROLL_MIN  31
#define ROLL_MAX 847

/**
 * Enable your AUX here and set the possible states.
 *
 * AUX mode may either be SWITCH if you have a mechanical switch attached, TRI
 * if you want to switch between low, mid and high with a momentary switch or
 * ONOFF if you want to switch between low and high with a momentary switch.
 */
#define AUX_1_ENABLE true
#define AUX_2_ENABLE true
#define AUX_3_ENABLE false
#define AUX_4_ENABLE false

#define AUX_1_MODE SWITCH_ONOFF
#define AUX_2_MODE DIGITAL_TRI
#define AUX_3_MODE DIGITAL_ONOFF
#define AUX_4_MODE SWITCH_TRI

/**
 * Enable serial debugging
 *
 * Be carefull this will mess with the signal emmiting timings. Only enable if
 * you are planning on developing.
 */
#define DEBUG false

/**
 * Enable buzzer
 *
 * When the buzzer is enabled, the controller will beep three times when
 * switching on the device. Also the buzzer is triggered when digital AUX
 * channels are changed or when the trims are pressed.
 */
 #define BUZZER true

/**
 * High or Low active
 *
 * Set if your buttons are HIGH or LOW active.
 */
#define ACTIVE LOW

/**
 * Enable internal pullups only if you are low active and do not have your
 * own pullups in place.
 */
#define ENABLE_PULLUPS true

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
#define MAXPULSE    1675
#define MINPULSE     675
#define SYNCPULSE    800
#define STOPULSE     300

/**
 * The positions where the trim values are saved in the EEPROM, you should not
 * need to touch this values.
 */
#define THROTTLE_TRIM_SAVE 0
#define YAW_TRIM_SAVE      2
#define PITCH_TRIM_SAVE    4
#define ROLL_TRIM_SAVE     6

#endif

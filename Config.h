#ifndef Config_h
#define Config_h
/**
 * Global configuration
 *
 * @author Chris Landa
 * @version 1.0 12.08.2012
 */

/**
 * Input Modes
 */
#define ONOFF 0
#define TRI 1
#define ANALOG -1

/**
 * Define if HIGH or LOW active buttons
 */
#define ACTIVE HIGH

/** 
 * Details about the PPM Pulse
 * 
 * One PPM Pulse is 700-1700 ms long, after each pulse there comes a 300ms Stop Pulse
 */
#define MAXPULSE 1700
#define MINPULSE 700
#define STOPULSE 300

/** Amount of channels the RX supports */
#define CHANNELS 8

/** 
 * If debugginging should be enabled
 */
#define DEBUG false		

/** If trimming should be enabled */
#define TRIM true

#endif
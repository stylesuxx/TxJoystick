#ifndef Config_h
#define Config_h
/**
 * Common defines
 *
 * @author Chris Landa
 */

/* High or Low active */
#define ACTIVE HIGH

/* Enable serial debugging */
#define DEBUG true

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

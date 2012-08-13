==============
= TxJoystick =
==============
Arduino based R/C transmitter with support of up to 8 PPM channels.

This software was written for the control of a quadrocopter with 4 analog input channels for steering and 4 digital inputs for various other tasks like arm/disarm or switching sensor modes.
It is easy adaptable for use with other devices like R/C planes or cars.

############
# Features #
############
* Analog input with and without digital trims
* Digital input for AUX, with two or three state mode
* Easy configuration

##########
# Wiring #
##########
For the Arduino Pro Mini 16Mhz/5V 
This should also work for all other models.
You may also adapt the settings in the main sketch file.
The digital input pins may be HIGH or LOW active and can be set in Config.h

PIN  |  FUNCTION
----------------
A0   |  Throllte
A1   |  Yaw
A2   |  Pitch
A3   |  Roll
     |
2    |  Trim up Roll
3    |  Trim down Roll
4    |  Trim up Pitch
5    |  Trim down Pitch
6    |  Trim up Yaw
7    |  Trim down Yaw
     |
8    |  AUX 1
     |
10   |  PPM Signal out

TODO:
* add buzzer support
* ass serial out for AUX states
* write more documentation ;-)

# TxJoystick
Arduino based R/C transmitter with support of up to 8 PPM channels.

This software was written for the control of a quadrocopter with 4 analog input channels for steering and 4 digital inputs for various other tasks like arm/disarm or switching sensor modes.
It is easy adaptable for use with other devices like R/C planes or cars.

## Features
* Analog input with and without digital trims
* Digital input for AUX, with two or three state mode
* Easy configuration

## Wiring
For the Arduino Pro Mini 16Mhz/5V 
This should also work for all other models.
You may also adapt the settings in the main sketch file.
The digital input pins may be HIGH or LOW active and can be set in Config.h

<table>
  <thead>
    <tr><th>PIN</th><th>FUNCTION</th></tr>
  </thead>
  <tbody>
    <tr><td>A0</td><td>Throllte
    <tr><td>A1</td><td>Yaw
    <tr><td>A2</td><td>Pitch</td></tr>
    <tr><td>A3</td><td>Roll</td></tr>
    <tr><td>2</td><td>Trim up Roll</td></tr>
    <tr><td>3</td><td>Trim down Roll</td></tr>
    <tr><td>4</td><td>Trim up Pitch</td></tr>
    <tr><td>5</td><td>Trim down Pitch</td></tr>
    <tr><td>6</td><td>Trim up Yaw</td></tr>
    <tr><td>7</td><td>Trim down Yaw</td></tr>
    <tr><td>8</td><td>AUX 1</td></tr>
    <tr><td>10</td><td>PPM Signal out</td></tr>
  </tbody>
</table>

##TODO
* add buzzer support
* ass serial out for AUX states
* write more documentation ;-)

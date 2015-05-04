# TxJoystick 1.4.0
Arduino based R/C PPM transmitter.

This software was written for the control of a quadrocopter with 4 analog input channels for steering and multiple digital inputs for various other tasks like arming, toggling LED's or switching sensor modes.

## Features
* Support for unlimited number of channels (limited by the number of channels supported by your receiver)
* Steering channels may be set trimmable, inverted and adjusted for your needs
* Digital and analog input for AUX, with two or three states
* Audio/LED feedback through buzzer pin
* Easy configuration through config file


## Wiring
This has been tested on an Arduino Pro Mini 16Mhz/5V but should also work for all other models.

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
    <tr><td>9</td><td>AUX 2</td></tr>
    <tr><td>11</td><td>AUX 3</td></tr>
    <tr><td>13</td><td>AUX 4</td></tr>
    <tr><td>10</td><td>PPM Signal</td></tr>
    <tr><td>12</td><td>Buzzer</td></tr>
  </tbody>
</table>

## Configuration
Read trough the **Config.h** file to see all possible settings you can adjust to
your needs.

Every setting has its comment describing the functionality - feel free to drop a comment if you feel a setting needs more explanations or the explanations are unclear.

## TODO:
* Three state momentary, analog AUX switch
OnOff contains code for a basic on-off controller (simple and hysteresis included)

PID.ino is the code which implements a basic PID controller, based on the PID_v1 Library.

Type "Setpoint,Kp,Ki,Kd" via Serial to the Arduino to dynamically set the constants.

Codes also include an SD module for data logging, operated using SPI (SS default @Pin 53)

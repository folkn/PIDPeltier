# PIDPeltier
PID Controller using the Arduino and numPy.
Written as a project for a basic Control Systems course

Outputs a PWM signal, which can be filtered to a DC voltage that is sent to the Peltier device.
The Arduino code processes the PID constants and outputs the results.
The feedback loop is taken using a K-Type thermocouple and the MAX6675 Thermocouple Amplifier.
The code can be modified to control any simple device using PID.
The Python code outputs the controller's output on a graph.
MATLAB graphing codes and sample raw data are also provided for reference.

Required Libraries:

PYTHON : pyserial, numpy, matplotlib, drawnow

ARDUINO: PID_v1, max6675

Libraries and software belong to their respective owners.


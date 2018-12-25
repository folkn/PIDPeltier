#include <PID_v1.h>
#include <math.h>
#include "max6675.h"
#include <SPI.h>
#include <SD.h>

//Pins
const int pinEN  = 8;
const int pinIn1 = 11;
const int pinIn2 = 12;
const int pinKDO = 6;
const int pinKCS = 5;
const int pinKCL = 4;
const int pinKVcc = 3;
const int pinKGnd = 2;
const int chipSelect = 53;

//Initialize Thermocouple
MAX6675 thermocouple(pinKCL, pinKCS, pinKDO);

//Initial PID terms
double Kp;
double Ki;
double Kd;
double Setpoint, Input, lastInput, Output, outputSum;
const int pidSampleRate = 1; //rate to calculate PID
unsigned long timePID; //Last PID Calculation
const float outputBoundary [2] = { -255, 255};
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
//Serial
const float serialRate = 500.0; //rate to output to Serial (ms)
unsigned long timeNow, timeLastSerial, timeLastTemp;

void setup() {
  //Serial
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  while (!Serial.available()) {
    ;
  }
  SD.begin(chipSelect);
  readSerial();


  //PWM Frequency to 31 kHz
  TCCR4B = TCCR4B  & 0b11111000 | 0x01;

  //Pin Initialization
  pinMode(LED_BUILTIN, OUTPUT); digitalWrite(LED_BUILTIN, 1);
  pinMode(pinEN, OUTPUT); digitalWrite(pinEN, LOW);
  pinMode(pinIn1, OUTPUT);
  pinMode(pinIn2, OUTPUT);
  pinMode(pinKVcc, OUTPUT); digitalWrite(pinKVcc, HIGH);
  pinMode(pinKGnd, OUTPUT); digitalWrite(pinKGnd, LOW);

  //PID Setup
  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(pidSampleRate); //Sets the sample rate
  myPID.SetOutputLimits(-255, 255);

  delay(1000);
  timeLastSerial = millis();
  timeLastTemp = millis();
}

void loop() {
  if (millis() - timeLastTemp >= 200.0) {
    Input = float(thermocouple.readCelsius());  //temp
    timeLastTemp = millis();
  }
  myPID.Compute();
  if (Output >= 0) {
    digitalWrite(pinIn1, HIGH);
    digitalWrite(pinIn2, LOW);
  } else {
    digitalWrite(pinIn1, LOW);
    digitalWrite(pinIn2, HIGH);
  }
  analogWrite(pinEN, abs(Output));

  doSerial();


}

void doSerial() {
 
 if (millis() - float(timeLastSerial) > serialRate) {
     File dataFile = SD.open("log.txt", FILE_WRITE);
    
  String dataText = String((millis() - 1000) / 1000.0, 3) + "," + String(Setpoint) + "," + String(Input) + "," + String(Output) + "," + String(Kp) + "," + String(Ki) + "," + String(Kd);
 
    Serial.println(dataText);

   if (dataFile) {
    dataFile.println(dataText);
   }
    dataFile.close();
  delay(100);
    if (Serial.available() > 0) { //Serial Cmd sent as:  "setpoint,Kp,Ki,Kd"
      readSerial();
    }
    timeLastSerial = millis();
   

  
  }
}
void readSerial() {
  
  float newSetpoint = Serial.parseFloat();
  Setpoint = newSetpoint > 0 ? newSetpoint : Setpoint;
  float newKp = Serial.parseFloat();
  Kp = newKp > 0 ? newKp : Kp;
  float newKi = Serial.parseFloat();
  Ki = newKi > 0 ? newKi : Ki;
  float newKd = Serial.parseFloat();
  Kd = newKd > 0 ? newKd : Kd;
  for (int i = Serial.available(); i == 0; i--) {
    Serial.read();  //Clears serial buffer
  }
  // Serial.println("SP:" + String(Setpoint) + ",Kp:" + String(Kp) + ",Ki:" + String(Ki) + ",Kd:" + String(Kd));
  myPID.SetTunings(Kp, Ki, Kd);
}
void computePID() {
  if (millis() - timePID > pidSampleRate) {
    double error = Setpoint - Input;
    double dInput = Input - lastInput;
    outputSum = Ki * error;

    if (outputSum > outputBoundary[1]) outputSum = outputBoundary[1];
    else if (outputSum < outputBoundary[0]) outputSum = outputBoundary[0];

    Output = outputSum - Kd * dInput;

    if (Output > outputBoundary[1]) Output = outputBoundary[1];
    else if (Output < outputBoundary[0]) Output = outputBoundary[0];

  }
  timeLastSerial = millis();
  lastInput = Input;
  return 1;

}

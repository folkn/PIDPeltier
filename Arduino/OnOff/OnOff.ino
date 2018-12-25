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

double Setpoint=50.0, Input, Output;

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


  //PWM Frequency to 31 kHz
  TCCR4B = TCCR4B  & 0b11111000 | 0x01;

  //Pin Initialization
  pinMode(LED_BUILTIN, OUTPUT); digitalWrite(LED_BUILTIN, 1);
  pinMode(pinEN, OUTPUT); digitalWrite(pinEN, LOW);
  pinMode(pinIn1, OUTPUT);
  pinMode(pinIn2, OUTPUT);
  pinMode(pinKVcc, OUTPUT); digitalWrite(pinKVcc, HIGH);
  pinMode(pinKGnd, OUTPUT); digitalWrite(pinKGnd, LOW);

  delay(1000);
  timeLastSerial = millis();
  timeLastTemp = millis();
}

void loop() {
  if (millis() - timeLastTemp >= 200.0) {
    Input = float(thermocouple.readCelsius());  //temp
    timeLastTemp = millis();
  }
 /*  //For one threshold controllerer
 if (Input < 50) {
    Output = 255;
  }
 // else {//For on-off one-direction control
///    Output = 0;
//  }
  else if(Input>=50) {//For on-off bidirectional control
    Output = -255;
  }*/
  //For a two threshold(deadband) controller
  if(Input>=52) {Output = -255;}
  if(Input<=48) {Output = 255;}
  if(Input>48 && Input < 52) {Output=0;} //for inactive deadband
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

    String dataText = String((millis() - 1000) / 1000.0, 3) + "," + String(Setpoint) + "," + String(Input) + "," + String(Output)+",0,0,0";

    Serial.println(dataText);

    if (dataFile) {
      dataFile.println(dataText);
    }
    dataFile.close();

    timeLastSerial = millis();


  }
}

/*
  PrintData.ino - Example using the SimpleINA226 library for communicating
  between Arduino and INA226 current monitor chip. Works with ESP8266.
  Created by Dominic Peters, July 5th, 2017.
  Released into the public domain.
*/

#include <Simple-INA226.h>

SIMPLE_INA226 ina;

float SHUNT_mOHM = 100;
float MAX_AMPS = 10;

void setup() {
  Serial.begin(115200);
  delay(1000);
  ina.init(MAX_AMPS, SHUNT_mOHM);
}

void loop() {

  Serial.print(" Volt: ");
  Serial.print(ina.getVoltage());
  Serial.print(" V, Current: ");
  Serial.print(ina.getCurrent());
  Serial.print(" A, Power: ");
  Serial.print(ina.getPower());
  Serial.print(" W");
  Serial.println();
  yield;
  delay(1000);
}

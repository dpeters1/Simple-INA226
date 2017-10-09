/*
  Simple-INA226.cpp - Library for communicating between Arduino and INA226 current monitor chip. Works with ESP8266.
  Created by Dominic Peters, July 5th, 2017.
  Released into the public domain.
*/

#include <Wire.h>
#include "Simple-INA226.h"

SIMPLE_INA226::SIMPLE_INA226() {}

void SIMPLE_INA226::init(float maxAmps, float resistorVal) {
    Wire.begin();
    writeRegister(INA226_CONFIG_REG, INA226_CONFIGURATION);
    _CURRENT_LSB = maxAmps / 32768;
    uint16_t calibration = 0.00512 / (_CURRENT_LSB*resistorVal/1000);
    writeRegister(INA226_CALIBRATION_REG, calibration);
}

void SIMPLE_INA226::writeRegister(uint8_t reg, uint16_t value) {
    Wire.beginTransmission(INA226_ADDR);
    Wire.write(reg);
    Wire.write((value >> 8) & 0xFF);
    Wire.write(value & 0xFF);
    Wire.endTransmission();
}

uint16_t SIMPLE_INA226::readRegister(uint8_t reg) {
    uint16_t res = 0x0000;
    Wire.beginTransmission(INA226_ADDR);
    Wire.write(reg);
    if (Wire.endTransmission() == 0) {
        if (Wire.requestFrom(INA226_ADDR, 2) >= 2) {
        res  = Wire.read() * 256;
        res += Wire.read();
        }
    }
    return res;
}

float SIMPLE_INA226::getShuntVoltage() {
    float volt = readRegister(INA226_SHUNT_VOLTAGE_REG) * VOLTAGE_LSB;
    return volt;
}

float SIMPLE_INA226::getVoltage() {
    float volt = readRegister(INA226_VOLTAGE_REG) * VOLTAGE_LSB;
    return volt;
}

float SIMPLE_INA226::getCurrent() {
    float current = readRegister(INA226_CURRENT_REG) * _CURRENT_LSB;
    return current;
}

float SIMPLE_INA226::getPower() {
    float power = readRegister(INA226_POWER_REG) * _CURRENT_LSB * POWER_LSB;
    return power;
}
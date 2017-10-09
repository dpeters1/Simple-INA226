/*
  Simple-INA226.h - Library for communicating between Arduino and INA226 current monitor chip. Works with ESP8266.
  Created by Dominic Peters, July 5th, 2017.
  Released into the public domain.
*/
#ifndef SIMPLE_INA226_h
    #define SIMPLE_INA226_h

#include "Arduino.h"

const float VOLTAGE_LSB = 0.00125;
const float POWER_LSB = 25;
const uint8_t INA226_CONFIG_REG = 0;          // Register locations
const uint8_t INA226_SHUNT_VOLTAGE_REG = 1;
const uint8_t INA226_VOLTAGE_REG = 2;
const uint8_t INA226_POWER_REG = 3;
const uint8_t INA226_CURRENT_REG = 4;
const uint8_t INA226_CALIBRATION_REG = 5;
const uint16_t INA226_ADDR = 0x40;            // SDA/SCL address of device
const uint16_t INA226_CONFIGURATION = 0x4427; // Device configuration - 0x4427 corresponds to:
                                              // Bus and Shunt Voltage Conversion time: 1.1ms
                                              // Sample Averages: 16
                                              // Operating Mode: Shunt and Bus, Continuous

class SIMPLE_INA226 {
  public:
    SIMPLE_INA226();
    void init(float maxAmps, float resistorVal); // MaxAmps in Amps, resistorVal in microOhms
    float getShuntVoltage();
    float getVoltage();
    float getCurrent();
    float getPower();


  private:
    void writeRegister(uint8_t reg, uint16_t value);
    uint16_t readRegister(uint8_t reg);
    float _CURRENT_LSB = 0;
};

#endif
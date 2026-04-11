#pragma once
#include <stdint.h>
#include "main.h"

class FuelGauge {
private:
    I2C_HandleTypeDef* i2c_handle;
    static const uint8_t I2C_ADDR_7BIT = 0x0B;
    static const uint8_t REG_IC_VERSION = 0x11;

public:
    FuelGauge(I2C_HandleTypeDef* handle); // Dependency injection
    bool ping(); // Return true if IC responds valid
};
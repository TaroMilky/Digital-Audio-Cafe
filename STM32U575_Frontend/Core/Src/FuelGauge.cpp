#include "FuelGauge.h"

FuelGauge::FuelGauge(I2C_HandleTypeDef* handle) : i2c_handle(handle) {
    // Initialization via member initializer list
}

bool FuelGauge::ping() {
    uint16_t version_data = 0;

    // TODO: Calculate the 8-bit shifted address
    // TODO: Write the HAL_I2C_Mem_Read() function here

    // The LC709203F IC version usually returns a specific hex value (e.g., 0x0003)
    // For now, if we get ANYTHING other than 0 or a HAL_ERROR, the bus is alive.
    if (version_data > 0) {
        return true;
    }
    return false;
}
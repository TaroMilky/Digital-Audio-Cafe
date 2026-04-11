#pragma once
#include "main.h"
#include "FuelGauge.h"

class AppOrchestrator {
private:
    FuelGauge battery_monitor;

public:
    AppOrchestrator(I2C_HandleTypeDef* hi2c_battery);
    void init();
    void run();
};
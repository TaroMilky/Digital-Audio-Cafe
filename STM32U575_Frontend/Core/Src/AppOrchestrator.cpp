#include "AppOrchestrator.h"

AppOrchestrator::AppOrchestrator(I2C_HandleTypeDef* hi2c_battery) : battery_monitor(hi2c_battery) {

}

void AppOrchestrator::init() {
    bool is_battery_alive = battery_monitor.ping();
}

void AppOrchestrator::run() {
    // main execution loop
}
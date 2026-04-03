#include <Arduino.h>
#include "CommsManager.h"

extern HardwareSerial manager_uart;

CommsManager::CommsManager() {
    rx_index = 0;
}

void CommsManager::init() {
    manager_uart.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);
}


// update() is a "else if" nest now, but later in the project 
// it will be transformed into a dictionary based function


void CommsManager::update() {
    if (manager_uart.available() > 0) {
        char incoming_byte = manager_uart.read();
        if (incoming_byte == '\n') {
            rx_buffer[rx_index] = '\0';
            
            if (sscanf(rx_buffer, "VOL:%f", &current_volume) == 1) {
            }
            else if (sscanf(rx_buffer, "SMOOTH:%f", &current_smoothing) == 1) {
            }
            rx_index = 0; // Clear Buffer
        } 
        else if (rx_index < 19) { // 19 leaves room for '\0' at the end
            rx_buffer[rx_index] = incoming_byte;
            rx_index++;
        }
    }
}

float CommsManager::get_volume() {
    return current_volume;
}

float CommsManager::get_smoothing() {
    return current_smoothing;
}
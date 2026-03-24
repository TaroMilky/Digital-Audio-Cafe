#include <Arduino.h>
#include "CommsManager.h"
#include "AudioPlayer.h"

// Global Variables
int last_volume = -1;

// Global Objects
HardwareSerial ManagerUART(1); // Claims UART 1 (UART 0 is for USB Serial monitor)
CommsManager frontend;
AudioPlayer audio;

void setup() {

    Serial.begin(115200);
    frontend.init();
    audio.init();

}

void loop() {

    frontend.update();

    int fetched_volume = frontend.getVolume(); // Current "system volume"

    // Debugging CommsManager
    if (fetched_volume != last_volume) {
        Serial.print("esp_volume:");
        Serial.println(fetched_volume);
        last_volume = fetched_volume;
    }

    audio.playSineWave(fetched_volume);

}
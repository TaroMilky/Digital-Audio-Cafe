#include <Arduino.h>
#include "InputManager.h"
#include "DisplayManager.h"
#include "MusicPlayer.h"

// Global Objects
InputManager input;
DisplayManager display;
MusicPlayer player;

int currentVol = 50; // Start at 50% volume

void setup() {
    Serial.begin(115200);
    
    // 2 seconds to open the monitor before printing anything
    delay(2000); 

    Serial.println("\n--- DIGITAL AUDIO CAFE: ONLINE ---");
    
    input.init();
    display.init();
    player.init();
    
    display.drawInterface();
    display.updateVolume(currentVol); 
}

void loop() {
    InputEvent e = input.poll();

    // IF logic to handle inputs
    if (e == EVENT_VOL_UP) {
        currentVol += 2; 
        if(currentVol > 100) currentVol = 100;
        
        player.setVolume(currentVol);
        display.updateVolume(currentVol);
        Serial.printf("Vol: %d (UP)\n", currentVol);
    }
    else if (e == EVENT_VOL_DOWN) {
        currentVol -= 2;
        if(currentVol < 0) currentVol = 0;
        
        player.setVolume(currentVol);
        display.updateVolume(currentVol);
        Serial.printf("Vol: %d (DOWN)\n", currentVol);
    }
    else if (e == EVENT_SELECT) {
        display.drawTest(); // Flash Red
        delay(100);
        display.drawInterface(); // Redraw UI
        display.updateVolume(currentVol); // Restore volume bar
    }
}
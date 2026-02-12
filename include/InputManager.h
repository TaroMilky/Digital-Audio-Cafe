#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <Arduino.h>

// --- PIN DEFINITIONS ---
#define PIN_ENC_A    10
#define PIN_ENC_B    11
#define PIN_ENC_BTN  12

#define PIN_JOY_UP   13
#define PIN_JOY_DOWN 14
#define PIN_JOY_LEFT 9
#define PIN_JOY_RIGHT 3
#define PIN_JOY_MID  46
#define PIN_BTN_SET  18
#define PIN_BTN_RST  8

// --- EVENT TYPES ---
enum InputEvent {
    EVENT_NONE = 0,
    EVENT_UP,
    EVENT_DOWN,
    EVENT_LEFT,
    EVENT_RIGHT,
    EVENT_SELECT,   
    EVENT_BACK,     
    EVENT_HOME,     
    EVENT_VOL_UP,   
    EVENT_VOL_DOWN, 
    EVENT_PLAY_PAUSE
};

class InputManager {
private:
    unsigned long lastDebounceTime = 0;
    
    // Encoder Variables
    uint8_t _oldEncState = 0;
    int8_t _encPulses = 0; // NEW: Counts the sub-steps

    struct ButtonMap {
        uint8_t pin;
        uint8_t lastState;
        InputEvent event;
    };
    
    ButtonMap _buttons[8];

public:
    InputManager();
    void init();
    InputEvent poll(); 
};

#endif
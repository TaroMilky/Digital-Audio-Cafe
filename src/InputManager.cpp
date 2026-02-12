#include "InputManager.h"

// --- ENCODER STATE TABLE ---
// 0=No Move, 1=CW, -1=CCW
const int8_t ENC_STATES[] = {
    0, -1,  1,  0,
    1,  0,  0, -1,
   -1,  0,  0,  1,
    0,  1, -1,  0
};

InputManager::InputManager() {
    // Map pins to events
    _buttons[0] = {PIN_JOY_UP,    HIGH, EVENT_UP};
    _buttons[1] = {PIN_JOY_DOWN,  HIGH, EVENT_DOWN};
    _buttons[2] = {PIN_JOY_LEFT,  HIGH, EVENT_LEFT};
    _buttons[3] = {PIN_JOY_RIGHT, HIGH, EVENT_RIGHT};
    _buttons[4] = {PIN_JOY_MID,   HIGH, EVENT_SELECT};
    _buttons[5] = {PIN_BTN_SET,   HIGH, EVENT_BACK};
    _buttons[6] = {PIN_BTN_RST,   HIGH, EVENT_HOME};
    _buttons[7] = {PIN_ENC_BTN,   HIGH, EVENT_PLAY_PAUSE};
}

void InputManager::init() {
    pinMode(PIN_ENC_A, INPUT_PULLUP);
    pinMode(PIN_ENC_B, INPUT_PULLUP);
    
    for(int i=0; i<8; i++) {
        pinMode(_buttons[i].pin, INPUT_PULLUP);
    }

    // Read initial encoder state
    _oldEncState = (digitalRead(PIN_ENC_A) << 1) | digitalRead(PIN_ENC_B);
    _encPulses = 0;
    
    Serial.println("[Input] Input Manager Initialized (1/4 Step Mode)");
}

InputEvent InputManager::poll() {
    InputEvent detectedEvent = EVENT_NONE;
    unsigned long currentTime = millis();

    // --- 1. ENCODER READING (Accumulator) ---
    uint8_t newEncState = (digitalRead(PIN_ENC_A) << 1) | digitalRead(PIN_ENC_B);
    
    if (newEncState != _oldEncState) {
        // Calculate direction (-1 or +1)
        uint8_t index = (_oldEncState << 2) | newEncState;
        int8_t direction = ENC_STATES[index & 0x0F];
        
        // Add to our "Pulse Jar"
        if (direction != 0) {
            _encPulses += direction;
        }

        // --- THE FIX: Only fire if we have 4 pulses ---
        // Change '4' to '2' if your encoder feels sluggish (skips clicks)
        if (_encPulses >= 4) {
            detectedEvent = EVENT_VOL_DOWN;
            _encPulses = 0; // Reset
        }
        else if (_encPulses <= -4) {
            detectedEvent = EVENT_VOL_UP;
            _encPulses = 0; // Reset
        }
        
        _oldEncState = newEncState;
        
        // Priority return
        if (detectedEvent != EVENT_NONE) return detectedEvent;
    }

    // --- 2. BUTTON EDGE DETECTION ---
    if ((currentTime - lastDebounceTime) > 20) {
        for(int i=0; i<8; i++) {
            int reading = digitalRead(_buttons[i].pin);

            // Falling Edge (Released -> Pressed)
            if (reading == LOW && _buttons[i].lastState == HIGH) {
                detectedEvent = _buttons[i].event;
                lastDebounceTime = currentTime; 
            }
            
            _buttons[i].lastState = reading;
            if (detectedEvent != EVENT_NONE) break; 
        }
    }

    return detectedEvent;
}
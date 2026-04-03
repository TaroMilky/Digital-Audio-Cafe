#pragma once

class CommsManager {

private:
    static const int TX_PIN = 4;
    static const int RX_PIN = 5;
    char rx_buffer[20];
    int rx_index = 0;
    float current_volume = 0.0f;
    float current_smoothing = 0.033f;

public:
    CommsManager();

    void init();
    void update();
    float get_volume();
    float get_smoothing();
};
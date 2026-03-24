#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H
#include <driver/i2s.h>

class AudioPlayer {

private:
    static const int BCK_PIN = 48;
    static const int DIN_PIN = 47;
    static const int LCK_PIN = 21;
    i2s_port_t i2s_port = I2S_NUM_0;

public:
    void init();
    void playSineWave(int volume);
};

#endif
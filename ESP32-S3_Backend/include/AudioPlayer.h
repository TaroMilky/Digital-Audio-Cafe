#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include <freertos/FreeRTOS.h>
#include <freertos/stream_buffer.h>
#include <driver/i2s.h>
#include <SPI.h>
#include "SdFat.h"

class AudioPlayer {

private:
    StreamBufferHandle_t audioBuffer;
    uint8_t* bufferStorage;                             // Pointer to the audio byte array in PSRAM
    StaticStreamBuffer_t* bufferStruct;                 // Pointer to the FreeRTOS management struct in PSRAM
    static const size_t AUDIO_BUFFER_SIZE = 128 * 1024; // 128KB buffer

    SdFs sd; // SD object
    // FsFile audioFile;
    SPIClass spiBus{FSPI};
    static const int SD_CS = 18;
    static const int SD_MOSI = 17;
    static const int SD_SCK = 16;
    static const int SD_MISO = 15;

    static const int BCK_PIN = 12;
    static const int DIN_PIN = 13;
    static const int LCK_PIN = 14;
    i2s_port_t i2s_port = I2S_NUM_0;

    float current_volume = 0.0f;
    float target_volume = 0.0f;
    float smoothing_factor = 0.0f;

public:
    void init();
    bool initSDCard();
    static void audioTaskTrampoline(void* _thisInstance);
    void audioTask();
    // bool openAudioFile(const char* filename);
    void setVolume(float target_volume_from_main);
    void setSmoothingFactor(float smoothing_factor_from_main);
    void playSineWave();
};

#endif
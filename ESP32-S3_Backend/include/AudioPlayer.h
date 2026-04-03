#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/stream_buffer.h>
#include <driver/i2s.h>

// Services
#include "SDManager.h"

class AudioPlayer {

private:
    SDManager sd_manager;

    StreamBufferHandle_t audio_buffer;
    uint8_t* buffer_storage;                               // Pointer to the audio byte array in PSRAM
    StaticStreamBuffer_t* buffer_struct;                   // Pointer to the FreeRTOS management struct in PSRAM
    static const size_t AUDIO_BUFFER_SIZE = 128 * 1024;   // 128KB buffer

    static const int BCK_PIN = 12;
    static const int DIN_PIN = 13;
    static const int LCK_PIN = 14;
    i2s_port_t i2s_port = I2S_NUM_0;

    float current_volume = 0.0f;
    float target_volume = 0.0f;
    float smoothing_factor = 0.0f;

public:
    void init();
    static void audio_task_trampoline(void* this_instance);
    void audio_task();
    void set_volume(float target_volume_from_main);
    void set_smoothing_factor(float smoothing_factor_from_main);
    void play_sine_wave();
};
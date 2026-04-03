#include <Arduino.h>
#include "CommsManager.h"
#include "AudioPlayer.h"

// Global Variables
float last_volume = -1.0f;
float fetched_volume = 0.0f;
float fetched_smoothing = 0.0f;

// Global Objects
HardwareSerial manager_uart(1); // Claims UART 1 (UART 0 is for USB Serial monitor)
CommsManager frontend;
AudioPlayer audio;
SemaphoreHandle_t audio_mutex;

void frontend_task(void *pv_parameters) {
    while(1) {
        vTaskDelay(10 / portTICK_PERIOD_MS); // delay for 10 ms (polling @100hz)

        frontend.update();

        if (xSemaphoreTake(audio_mutex, portMAX_DELAY) == pdTRUE) { // "Take" the key; if not available, wait
            fetched_volume = frontend.get_volume(); // Current "system volume"
            fetched_smoothing = frontend.get_smoothing(); // Current smoothing value
            xSemaphoreGive(audio_mutex); // "Give" the key back
        }

        // Debugging CommsManager
        if (fetched_volume != last_volume) {
            Serial.print("esp_volume:");
            Serial.println(fetched_volume);
            last_volume = fetched_volume;
        }
    }
}

void audio_task_main(void *pv_parameters) {
    while(1) {

        if (xSemaphoreTake(audio_mutex, portMAX_DELAY) == pdTRUE) { // "Take" the key; if not available, wait
            audio.set_volume(fetched_volume);
            audio.set_smoothing_factor(fetched_smoothing);
            xSemaphoreGive(audio_mutex); // "Give" the key back
        }

        audio.play_sine_wave();

    }
}

void setup() {

    // Hardware inits
    Serial.begin(115200);

    // DEBUGGING 3/29
    delay(3000);
    Serial.println("\n\n--- ESP32-S3 BOOTING ---");

    frontend.init();
    audio.init();

    // FreeRTOS tasks
    audio_mutex = xSemaphoreCreateMutex();

    xTaskCreatePinnedToCore(      
        frontend_task,      // 1. Pointer to the task function
        "frontend_task",    // 2. Name of task (for debugging, e.g., "audio_task_main")
        4096,              // 3. Stack size in words (Use 4096 or 8192 for now)
        NULL,              // 4. Parameter to pass to function (Usually NULL)
        1,                 // 5. Task priority (0 is lowest, 1 is normal, configMAX_PRIORITIES-1 is highest)
        NULL,              // 6. Task handle (NULL if you don't need to kill it later)
        0                  // 7. Core ID (0 or 1)
    );

    xTaskCreatePinnedToCore(      
        audio_task_main,         // 1. Pointer to the task function
        "audio_task_main",       // 2. Name of task (for debugging, e.g., "audio_task_main")
        4096,              // 3. Stack size in words (Use 4096 or 8192 for now)
        NULL,              // 4. Parameter to pass to function (Usually NULL)
        2,                 // 5. Task priority (0 is lowest, 1 is normal, configMAX_PRIORITIES-1 is highest)
        NULL,              // 6. Task handle (NULL if you don't need to kill it later)
        1                  // 7. Core ID (0 or 1)
    );

}

void loop() {

}
#include <Arduino.h>
#include "SDManager.h"

bool SDManager::init_sd_card() {
    spi_bus.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);

    // Next: Send UART to STM32, SD Card initialized/not
    if(!sd.begin(SdSpiConfig(SD_CS, DEDICATED_SPI, SD_SCK_MHZ(16), &spi_bus))) {
        Serial.println("SD Card Mount Failed!");
        return false;
    }
    Serial.printf("SD Card Mounted! FAT Type: FAT%d\n", sd.fatType());
    return true;
}

bool SDManager::open_audio_file(const char* filepath) {
    
    if (audio_file.isOpen()){
        audio_file.close();
    }

    audio_file = sd.open(filepath, O_READ);

    if (audio_file.isOpen()) {
        Serial.println("File opened!");
        return true;
    } else {
        Serial.println("File failed to open!");
        return false;
    }

}

size_t SDManager::read_audio_chunk(uint8_t* buffer, size_t bytes_to_read) {

    if (audio_file.isOpen()) {
        return audio_file.read(buffer, bytes_to_read);
    } else {
        return 0;
    }

}
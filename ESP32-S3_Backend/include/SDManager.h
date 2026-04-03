#pragma once

#include <SPI.h>
#include "SdFat.h"

class SDManager {

private:

    SdFs sd; // SD object
    FsFile audio_file;
    SPIClass spi_bus{FSPI};
    static const int SD_CS = 18;
    static const int SD_MOSI = 17;
    static const int SD_SCK = 16;
    static const int SD_MISO = 15;

public:

    bool init_sd_card();
    bool open_audio_file(const char* filepath);
    size_t read_audio_chunk(uint8_t* buffer, size_t bytes_to_read);

};
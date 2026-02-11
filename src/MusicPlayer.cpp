#include "MusicPlayer.h"

// Set defaults
MusicPlayer::MusicPlayer() {
    _currentState = STOPPED;
    _currentVolume = 50;
    _currentSongName = "";
}

void MusicPlayer::init() {
    // audio.setVolumeSteps(100);
    Serial.println("[Engine] Audio Engine Initialized");
}

void MusicPlayer::playFile(String filename) {
    _currentSongName = filename;
    _currentState = PLAYING;

    Serial.print("[Engine] Now Playing: ");
    Serial.println(_currentSongName);

    // ADD I2S AUDIO PLAYBACK CODE HERE
    // audio.connecttoFS(SD_MMC, filename.c_str());
}

void MusicPlayer::pause() {
    if (_currentState == PLAYING) {
        _currentState = PAUSED;
        Serial.println("[Engine] Paused");
    }
}

void MusicPlayer::resume() {
    if (_currentState == PAUSED) {
        _currentState = PLAYING;
        Serial.println("[Engine] Resumed");
    }
}

void MusicPlayer::setVolume(int volume) {
    // SC
    if (volume < 0) volume = 0;
    if (volume > 100) volume = 100;

    _currentVolume = volume;

    // audio.setVolume(_currentVolume);

    Serial.printf("[Engine] Volume set to: %d\n", _currentVolume);
}

PlayerState MusicPlayer::getState() {
    return _currentState;
}

String MusicPlayer::getSongName() {
    return _currentSongName;
}
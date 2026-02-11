#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include <Arduino.h>

enum PlayerState {
    STOPPED,
    PLAYING,
    PAUSED
};

class MusicPlayer {
private:
    PlayerState _currentState;
    int _currentVolume;
    String _currentSongName;

public:
    MusicPlayer();

    void init();
    void playFile(String filename);
    void pause();
    void resume();
    void setVolume(int volume);

    PlayerState getState();
    String getSongName();
};

#endif
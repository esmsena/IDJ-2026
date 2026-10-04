#ifndef MUSIC_H
#define MUSIC_H

#include <string>

#include "SDL_include.h"

class Music {
public:
    Music();
    explicit Music(const std::string& file);
    ~Music();

    void Play(int times = -1) const;
    void Stop(int msToStop = 1500) const;
    void Open(const std::string& file);
    bool IsOpen() const;

    Music(const Music&) = delete;
    Music& operator=(const Music&) = delete;

private:
    Mix_Music* music;
};

#endif

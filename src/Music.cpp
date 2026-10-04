#include "Music.h"

#include <iostream>

#include "Resources.h"

Music::Music() : music(nullptr) {}

Music::Music(const std::string& file) : Music() {
    Open(file);
}

Music::~Music() {
    Stop(0);
}

void Music::Play(int times) const {
    if (music != nullptr && Mix_PlayMusic(music, times) == -1) {
        std::cerr << "Nao foi possivel tocar a musica: " << Mix_GetError() << '\n';
    }
}

void Music::Stop(int msToStop) const {
    if (music != nullptr) {
        Mix_FadeOutMusic(msToStop);
    }
}

void Music::Open(const std::string& file) {
    music = Resources::GetMusic(file);
}

bool Music::IsOpen() const {
    return music != nullptr;
}

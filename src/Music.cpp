#include "Music.h"

#include <iostream>

#include "Resources.h"

Music::Music(const std::string& file) : music(Resources::GetMusic(file)) {}

Music::~Music() = default;

void Music::Play(int times) const {
    if (music != nullptr && Mix_PlayMusic(music, times) == -1) {
        std::cerr << "Nao foi possivel tocar a musica: " << Mix_GetError() << '\n';
    }
}

void Music::Stop(int msToStop) const {
    Mix_FadeOutMusic(msToStop);
}

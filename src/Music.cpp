#include "Music.h"

#include <iostream>

Music::Music(const std::string& file) : music(Mix_LoadMUS(file.c_str())) {
    if (music == nullptr && file.rfind("Recursos/", 0) != 0) {
        music = Mix_LoadMUS(("Recursos/" + file).c_str());
    }

    if (music == nullptr) {
        std::cerr << "Nao foi possivel carregar a musica '" << file
                  << "': " << Mix_GetError() << '\n';
    }
}

Music::~Music() {
    if (music != nullptr) {
        Mix_FreeMusic(music);
    }
}

void Music::Play(int times) const {
    if (music != nullptr && Mix_PlayMusic(music, times) == -1) {
        std::cerr << "Nao foi possivel tocar a musica: " << Mix_GetError() << '\n';
    }
}

void Music::Stop(int msToStop) const {
    Mix_FadeOutMusic(msToStop);
}

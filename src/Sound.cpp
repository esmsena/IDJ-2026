#include "Sound.h"

#include <iostream>

#include "Resources.h"

Sound::Sound() : chunk(nullptr), channel(-1) {}

Sound::Sound(const std::string& file) : Sound() {
    Open(file);
}

Sound::~Sound() {
    Stop();
}

void Sound::Play(int times) {
    if (chunk == nullptr) return;

    channel = Mix_PlayChannel(-1, chunk, times - 1);
    if (channel == -1) {
        std::cerr << "Nao foi possivel tocar o som: " << Mix_GetError() << '\n';
    }
}

void Sound::Stop() {
    if (chunk != nullptr && channel != -1) {
        Mix_HaltChannel(channel);
        channel = -1;
    }
}

void Sound::Open(const std::string& file) {
    Stop();
    chunk = Resources::GetSound(file);
}

bool Sound::IsOpen() const {
    return chunk != nullptr;
}

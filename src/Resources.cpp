#include "Resources.h"

#include <iostream>
#include <unordered_map>

#include "Game.h"

namespace {
std::unordered_map<std::string, SDL_Texture*> imageTable;
std::unordered_map<std::string, Mix_Music*> musicTable;
std::unordered_map<std::string, Mix_Chunk*> soundTable;

std::string ResourcePath(const std::string& file) {
    return file.rfind("Recursos/", 0) == 0 ? file : "Recursos/" + file;
}
}

SDL_Texture* Resources::GetImage(const std::string& file) {
    const std::string path = ResourcePath(file);
    const auto found = imageTable.find(path);
    if (found != imageTable.end()) return found->second;

    SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), path.c_str());
    if (texture == nullptr) {
        std::cerr << "Nao foi possivel carregar a imagem '" << path
                  << "': " << IMG_GetError() << '\n';
        return nullptr;
    }

    imageTable.emplace(path, texture);
    return texture;
}

Mix_Music* Resources::GetMusic(const std::string& file) {
    const std::string path = ResourcePath(file);
    const auto found = musicTable.find(path);
    if (found != musicTable.end()) return found->second;

    Mix_Music* music = Mix_LoadMUS(path.c_str());
    if (music == nullptr) {
        std::cerr << "Nao foi possivel carregar a musica '" << path
                  << "': " << Mix_GetError() << '\n';
        return nullptr;
    }

    musicTable.emplace(path, music);
    return music;
}

Mix_Chunk* Resources::GetSound(const std::string& file) {
    const std::string path = ResourcePath(file);
    const auto found = soundTable.find(path);
    if (found != soundTable.end()) return found->second;

    Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
    if (sound == nullptr) {
        std::cerr << "Nao foi possivel carregar o som '" << path
                  << "': " << Mix_GetError() << '\n';
        return nullptr;
    }

    soundTable.emplace(path, sound);
    return sound;
}

void Resources::ClearImages() {
    for (const auto& image : imageTable) SDL_DestroyTexture(image.second);
    imageTable.clear();
}

void Resources::ClearMusics() {
    for (const auto& music : musicTable) Mix_FreeMusic(music.second);
    musicTable.clear();
}

void Resources::ClearSounds() {
    for (const auto& sound : soundTable) Mix_FreeChunk(sound.second);
    soundTable.clear();
}

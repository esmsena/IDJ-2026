#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>

#include "SDL_include.h"

class Resources {
public:
    static SDL_Texture* GetImage(const std::string& file);
    static Mix_Music* GetMusic(const std::string& file);
    static Mix_Chunk* GetSound(const std::string& file);

    static void ClearImages();
    static void ClearMusics();
    static void ClearSounds();
};

#endif

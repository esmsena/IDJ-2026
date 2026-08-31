#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include "SDL_include.h"

class Sprite {
public:
    explicit Sprite(const std::string& file);
    ~Sprite();

    void Render(int x, int y) const;
    int GetWidth() const;
    int GetHeight() const;
    bool IsOpen() const;

    Sprite(const Sprite&) = delete;
    Sprite& operator=(const Sprite&) = delete;

private:
    SDL_Texture* texture;
    int width;
    int height;
};

#endif

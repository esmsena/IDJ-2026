#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include "SDL_include.h"

class Sprite {
public:
    Sprite();
    explicit Sprite(const std::string& file, int frameCountW = 1, int frameCountH = 1);
    ~Sprite();

    void Open(const std::string& file);
    void Render(int x, int y, int w, int h) const;
    void SetClip(int x, int y, int w, int h);
    void SetFrame(int frame);
    void SetFrameCount(int frameCountW, int frameCountH);
    int GetWidth() const;
    int GetHeight() const;
    bool IsOpen() const;

    Sprite(const Sprite&) = delete;
    Sprite& operator=(const Sprite&) = delete;

private:
    SDL_Texture* texture;
    int width;
    int height;
    SDL_Rect clipRect;
    int frameCountW;
    int frameCountH;
};

#endif

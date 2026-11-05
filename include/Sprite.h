#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include "SDL_include.h"
#include "Vec2.h"

class Sprite {
public:
    Sprite();
    explicit Sprite(const std::string& file, int frameCountW = 1, int frameCountH = 1);
    ~Sprite();

    void Open(const std::string& file);
    void Render(int x, int y, int w, int h, float angle = 0.0f) const;
    void SetClip(int x, int y, int w, int h);
    void SetFrame(int frame);
    void SetFrameCount(int frameCountW, int frameCountH);
    void SetScale(float scaleX, float scaleY);
    Vec2 GetScale() const;
    void SetFlip(SDL_RendererFlip flip);
    int GetWidth() const;
    int GetHeight() const;
    bool IsOpen() const;

    bool cameraFollower;

    Sprite(const Sprite&) = delete;
    Sprite& operator=(const Sprite&) = delete;

private:
    SDL_Texture* texture;
    int width;
    int height;
    SDL_Rect clipRect;
    int frameCountW;
    int frameCountH;
    SDL_RendererFlip flip;
    Vec2 scale;
};

#endif

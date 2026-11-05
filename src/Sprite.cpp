#include "Sprite.h"

#include "Camera.h"
#include "Game.h"
#include "Resources.h"

Sprite::Sprite()
    : cameraFollower(false), texture(nullptr), width(0), height(0),
      clipRect({0, 0, 0, 0}), frameCountW(1), frameCountH(1),
      flip(SDL_FLIP_NONE), scale(1.0f, 1.0f) {}

Sprite::Sprite(const std::string& file, int frameCountW, int frameCountH)
    : Sprite() {
    SetFrameCount(frameCountW, frameCountH);
    Open(file);
}

void Sprite::Open(const std::string& file) {
    width = 0;
    height = 0;
    clipRect = {0, 0, 0, 0};

    texture = Resources::GetImage(file);
    if (texture == nullptr) return;

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetFrame(0);
}

Sprite::~Sprite() = default;

// w e h ja chegam ajustados para a escala: vem da box, que SetScale mantem atualizada.
void Sprite::Render(int x, int y, int w, int h, float angle) const {
    if (texture == nullptr) {
        return;
    }

    SDL_Rect destination = {x, y, w, h};
    if (!cameraFollower) {
        destination.x -= static_cast<int>(Camera::pos.x);
        destination.y -= static_cast<int>(Camera::pos.y);
    }
    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &destination,
                     angle, nullptr, flip);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    if (x < 0 || y < 0 || w <= 0 || h <= 0 || x + w > width || y + h > height) {
        return;
    }

    clipRect = {x, y, w, h};
}

void Sprite::SetFrame(int frame) {
    const int totalFrames = frameCountW * frameCountH;
    if (texture == nullptr || frame < 0 || frame >= totalFrames) {
        return;
    }

    const int frameWidth = width / frameCountW;
    const int frameHeight = height / frameCountH;
    const int row = frame / frameCountW;
    const int column = frame % frameCountW;
    SetClip(column * frameWidth, row * frameHeight, frameWidth, frameHeight);
}

void Sprite::SetFrameCount(int newFrameCountW, int newFrameCountH) {
    if (newFrameCountW <= 0 || newFrameCountH <= 0) {
        return;
    }

    frameCountW = newFrameCountW;
    frameCountH = newFrameCountH;
    if (texture != nullptr) {
        SetFrame(0);
    }
}

void Sprite::SetScale(float scaleX, float scaleY) {
    if (scaleX != 0.0f) scale.x = scaleX;
    if (scaleY != 0.0f) scale.y = scaleY;
}

Vec2 Sprite::GetScale() const {
    return scale;
}

void Sprite::SetFlip(SDL_RendererFlip newFlip) {
    flip = newFlip;
}

int Sprite::GetWidth() const {
    return static_cast<int>(width / frameCountW * scale.x);
}

int Sprite::GetHeight() const {
    return static_cast<int>(height / frameCountH * scale.y);
}

bool Sprite::IsOpen() const {
    return texture != nullptr;
}

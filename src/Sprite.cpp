#include "Sprite.h"

#include <iostream>

#include "Game.h"

Sprite::Sprite()
    : texture(nullptr), width(0), height(0), clipRect({0, 0, 0, 0}),
      frameCountW(1), frameCountH(1) {}

Sprite::Sprite(const std::string& file, int frameCountW, int frameCountH)
    : Sprite() {
    SetFrameCount(frameCountW, frameCountH);
    Open(file);
}

void Sprite::Open(const std::string& file) {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    width = 0;
    height = 0;
    clipRect = {0, 0, 0, 0};

    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    texture = IMG_LoadTexture(renderer, file.c_str());

    if (texture == nullptr && file.rfind("Recursos/", 0) != 0) {
        texture = IMG_LoadTexture(renderer, ("Recursos/" + file).c_str());
    }

    if (texture == nullptr) {
        std::cerr << "Nao foi possivel carregar a imagem '" << file
                  << "': " << IMG_GetError() << '\n';
        return;
    }

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetFrame(0);
}

Sprite::~Sprite() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Render(int x, int y, int w, int h) const {
    if (texture == nullptr) {
        return;
    }

    SDL_Rect destination = {x, y, w, h};
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &destination);
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

int Sprite::GetWidth() const {
    return width / frameCountW;
}

int Sprite::GetHeight() const {
    return height / frameCountH;
}

bool Sprite::IsOpen() const {
    return texture != nullptr;
}

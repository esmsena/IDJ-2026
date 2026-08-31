#include "Sprite.h"

#include <iostream>

#include "Game.h"

Sprite::Sprite(const std::string& file) : texture(nullptr), width(0), height(0) {
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
}

Sprite::~Sprite() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Render(int x, int y) const {
    if (texture == nullptr) {
        return;
    }

    SDL_Rect destination = {x, y, width, height};
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, nullptr, &destination);
}

int Sprite::GetWidth() const {
    return width;
}

int Sprite::GetHeight() const {
    return height;
}

bool Sprite::IsOpen() const {
    return texture != nullptr;
}

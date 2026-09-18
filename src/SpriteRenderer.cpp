#include "SpriteRenderer.h"

#include "GameObject.h"

SpriteRenderer::SpriteRenderer(GameObject& associated)
    : Component(associated), sprite() {}

SpriteRenderer::SpriteRenderer(GameObject& associated, const std::string& file,
                               int frameCountW, int frameCountH)
    : Component(associated), sprite(file, frameCountW, frameCountH) {
    associated.box.w = static_cast<float>(sprite.GetWidth());
    associated.box.h = static_cast<float>(sprite.GetHeight());
    sprite.SetFrame(0);
}

void SpriteRenderer::Open(const std::string& file) {
    sprite.Open(file);
    associated.box.w = static_cast<float>(sprite.GetWidth());
    associated.box.h = static_cast<float>(sprite.GetHeight());
}

void SpriteRenderer::SetFrameCount(int frameCountW, int frameCountH) {
    sprite.SetFrameCount(frameCountW, frameCountH);
    associated.box.w = static_cast<float>(sprite.GetWidth());
    associated.box.h = static_cast<float>(sprite.GetHeight());
}

void SpriteRenderer::SetFrame(int frame) {
    sprite.SetFrame(frame);
}

void SpriteRenderer::Update(float) {}

void SpriteRenderer::Render() {
    sprite.Render(static_cast<int>(associated.box.x), static_cast<int>(associated.box.y),
                  static_cast<int>(associated.box.w), static_cast<int>(associated.box.h));
}

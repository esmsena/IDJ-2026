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

void SpriteRenderer::SetFrame(int frame, SDL_RendererFlip flip) {
    sprite.SetFrame(frame);
    sprite.SetFlip(flip);
}

void SpriteRenderer::SetScale(float scaleX, float scaleY) {
    const Vec2 center = associated.box.GetCenter();
    sprite.SetScale(scaleX, scaleY);
    associated.box.w = static_cast<float>(sprite.GetWidth());
    associated.box.h = static_cast<float>(sprite.GetHeight());
    associated.box.SetCenter(center);
}

void SpriteRenderer::SetCameraFollower(bool cameraFollower) {
    sprite.cameraFollower = cameraFollower;
}

void SpriteRenderer::Update(float) {}

void SpriteRenderer::Render() {
    sprite.Render(static_cast<int>(associated.box.x), static_cast<int>(associated.box.y),
                  static_cast<int>(associated.box.w), static_cast<int>(associated.box.h),
                  static_cast<float>(associated.angleDeg));
}

#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <string>

#include "Component.h"
#include "Sprite.h"

class SpriteRenderer : public Component {
public:
    explicit SpriteRenderer(GameObject& associated);
    SpriteRenderer(GameObject& associated, const std::string& file,
                   int frameCountW = 1, int frameCountH = 1);

    void Open(const std::string& file);
    void SetFrameCount(int frameCountW, int frameCountH);
    void SetFrame(int frame);
    void Update(float dt) override;
    void Render() override;

private:
    Sprite sprite;
};

#endif

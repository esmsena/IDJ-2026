#include "Bullet.h"

#include "GameObject.h"
#include "SpriteRenderer.h"

namespace {
const float BULLET_SCALE = 0.75f;
// O desenho da Bullet aponta para cima, e o angulo 0 aponta para a direita.
const float SPRITE_ANGLE_OFFSET = 90.0f;
}

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance)
    : Component(associated), speed(Vec2(speed, 0.0f).Rotated(angle)),
      distanceLeft(maxDistance), damage(damage) {
    auto* renderer = new SpriteRenderer(associated, "img/Bullet.png");
    renderer->SetScale(BULLET_SCALE, BULLET_SCALE);
    associated.AddComponent(renderer);
    associated.angleDeg = angle * RAD_TO_DEG + SPRITE_ANGLE_OFFSET;
}

void Bullet::Update(float dt) {
    const Vec2 movement = speed * dt;
    associated.box += movement;
    distanceLeft -= movement.Magnitude();
    if (distanceLeft <= 0.0f) {
        associated.RequestDelete();
    }
}

void Bullet::Render() {}

int Bullet::GetDamage() const {
    return damage;
}

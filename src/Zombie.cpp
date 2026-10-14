#include "Zombie.h"

#include "Animation.h"
#include "Animator.h"
#include "Camera.h"
#include "GameObject.h"
#include "InputManager.h"
#include "SpriteRenderer.h"

namespace {
const int CLICK_DAMAGE = 25;
const float HIT_DURATION = 0.5f;
const float CORPSE_DURATION = 5.0f;
}

Zombie::Zombie(GameObject& associated, int hitpoints)
    : Component(associated), hitpoints(hitpoints), deathSound("audio/Dead.wav"),
      hitSound("audio/Hit0.wav"), hit(false) {
    auto* renderer = new SpriteRenderer(associated, "img/Enemy.png", 3, 2);
    associated.AddComponent(renderer);

    auto* animator = new Animator(associated);
    animator->AddAnimation("walking", Animation(0, 3, 0.15f));
    animator->AddAnimation("hit", Animation(4, 4, 0.0f));
    animator->AddAnimation("dead", Animation(5, 5, 0.0f));
    animator->SetAnimation("walking");
    associated.AddComponent(animator);
}

void Zombie::Damage(int damage) {
    hitpoints -= damage;
    hitSound.Play(1);

    Animator* animator = associated.GetComponent<Animator>();
    if (hitpoints <= 0 && hitpoints + damage > 0) {
        hit = false;
        deathTimer.Restart();
        if (animator != nullptr) animator->SetAnimation("dead");
        deathSound.Play(1);
    } else if (hitpoints > 0) {
        hit = true;
        hitTimer.Restart();
        if (animator != nullptr) animator->SetAnimation("hit");
    }
}

void Zombie::Update(float dt) {
    hitTimer.Update(dt);

    if (hitpoints <= 0) {
        deathTimer.Update(dt);
        if (deathTimer.Get() > CORPSE_DURATION) {
            associated.RequestDelete();
        }
        return;
    }

    if (hit && hitTimer.Get() > HIT_DURATION) {
        hit = false;
        if (Animator* animator = associated.GetComponent<Animator>()) {
            animator->SetAnimation("walking");
        }
    }

    InputManager& input = InputManager::GetInstance();
    if (input.MousePress(LEFT_MOUSE_BUTTON)) {
        const Vec2 mouse(input.GetMouseX() + Camera::pos.x, input.GetMouseY() + Camera::pos.y);
        if (associated.box.Contains(mouse)) {
            Damage(CLICK_DAMAGE);
        }
    }
}

void Zombie::Render() {}

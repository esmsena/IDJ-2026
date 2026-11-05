#include "Gun.h"

#include <cmath>

#include "Animation.h"
#include "Animator.h"
#include "Bullet.h"
#include "Game.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "State.h"

namespace {
const float BODY_DISTANCE = 40.0f;
const float BARREL_LENGTH = 36.0f;

const float BULLET_SPEED = 800.0f;
const int BULLET_DAMAGE = 25;
const float BULLET_MAX_DISTANCE = 900.0f;

const float SHOT_TIME = 0.25f;
const float RELOAD_FRAME_TIME = 0.04f;
const float RELOAD_TIME = 6 * RELOAD_FRAME_TIME;
const float READY_TIME = 0.2f;

enum CooldownState { READY, AFTER_SHOT, RELOADING, RELOADED };
}

Gun::Gun(GameObject& associated, std::weak_ptr<GameObject> character)
    : Component(associated), shotSound("audio/Range.wav"), reloadSound("audio/PumpAction.mp3"),
      cooldownState(READY), character(character), angle(0.0f) {
    associated.AddComponent(new SpriteRenderer(associated, "img/Gun.png", 3, 2));

    auto* animator = new Animator(associated);
    animator->AddAnimation("idle", Animation(0, 0, 0.0f));
    animator->AddAnimation("idleFlipped", Animation(0, 0, 0.0f, SDL_FLIP_VERTICAL));
    animator->AddAnimation("reloading", Animation(0, 5, RELOAD_FRAME_TIME));
    animator->AddAnimation("reloadingFlipped", Animation(0, 5, RELOAD_FRAME_TIME, SDL_FLIP_VERTICAL));
    animator->SetAnimation("idle");
    associated.AddComponent(animator);
}

void Gun::Update(float dt) {
    const std::shared_ptr<GameObject> owner = character.lock();
    if (owner == nullptr) {
        associated.RequestDelete();
        return;
    }

    associated.box.SetCenter(owner->box.GetCenter() + Vec2(BODY_DISTANCE, 0.0f).Rotated(angle));
    associated.angleDeg = angle * RAD_TO_DEG;

    // A arma fica logo na frente do corpo, ou logo atras se estiver mirando para cima.
    const float sortDistance = std::sin(angle) < 0.0f ? -0.5f : 0.5f;
    associated.ySortOffset = owner->GetSortY() + sortDistance -
                             (associated.box.y + associated.box.h);

    cdTimer.Update(dt);
    if (cooldownState == AFTER_SHOT && cdTimer.Get() > SHOT_TIME) {
        cooldownState = RELOADING;
        cdTimer.Restart();
        reloadSound.Play(1);
        PlayAnimation("reloading");
    } else if (cooldownState == RELOADING && cdTimer.Get() > RELOAD_TIME) {
        cooldownState = RELOADED;
        cdTimer.Restart();
        PlayAnimation("idle");
    } else if (cooldownState == RELOADED && cdTimer.Get() > READY_TIME) {
        cooldownState = READY;
    }
}

void Gun::Render() {}

void Gun::Shoot(Vec2 target) {
    const std::shared_ptr<GameObject> owner = character.lock();
    if (owner == nullptr || cooldownState != READY) {
        return;
    }

    const Vec2 origin = owner->box.GetCenter();
    angle = (target - origin).Inclination();
    PlayAnimation("idle");

    shotSound.Play(1);
    cooldownState = AFTER_SHOT;
    cdTimer.Restart();

    auto* bullet = new GameObject();
    bullet->AddComponent(new Bullet(*bullet, angle, BULLET_SPEED, BULLET_DAMAGE,
                                    BULLET_MAX_DISTANCE));
    bullet->box.SetCenter(origin + Vec2(BODY_DISTANCE + BARREL_LENGTH, 0.0f).Rotated(angle));
    Game::GetInstance().GetState().AddObject(bullet);
}

void Gun::PlayAnimation(const std::string& name) {
    if (Animator* animator = associated.GetComponent<Animator>()) {
        // Mirando para a esquerda a arma giraria de cabeca para baixo.
        animator->SetAnimation(std::cos(angle) < 0.0f ? name + "Flipped" : name);
    }
}

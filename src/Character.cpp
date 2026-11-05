#include "Character.h"

#include "Animation.h"
#include "Animator.h"
#include "Camera.h"
#include "Game.h"
#include "GameObject.h"
#include "Gun.h"
#include "SpriteRenderer.h"
#include "State.h"

namespace {
const float DEATH_DURATION = 3.0f;
}

Character* Character::player = nullptr;

Character::Character(GameObject& associated, const std::string& sprite)
    : Component(associated), linearSpeed(250.0f), hp(100), facingLeft(false) {
    associated.AddComponent(new SpriteRenderer(associated, sprite, 3, 4));

    auto* animator = new Animator(associated);
    animator->AddAnimation("idle", Animation(6, 9, 0.2f));
    animator->AddAnimation("idleLeft", Animation(6, 9, 0.2f, SDL_FLIP_HORIZONTAL));
    animator->AddAnimation("walking", Animation(0, 5, 0.1f));
    animator->AddAnimation("walkingLeft", Animation(0, 5, 0.1f, SDL_FLIP_HORIZONTAL));
    animator->AddAnimation("dead", Animation(10, 11, 0.5f));
    animator->SetAnimation("idle");
    associated.AddComponent(animator);
}

Character::~Character() {
    if (player == this) {
        player = nullptr;
        Camera::Unfollow();
    }
}

void Character::Start() {
    State& state = Game::GetInstance().GetState();
    auto* gunObject = new GameObject();
    gunObject->AddComponent(new Gun(*gunObject, state.GetObjectPtr(&associated)));
    gun = state.AddObject(gunObject);
}

void Character::Update(float dt) {
    speed = Vec2();

    while (!taskQueue.empty()) {
        const Command task = taskQueue.front();
        taskQueue.pop();

        if (hp <= 0) continue;

        if (task.type == Command::MOVE) {
            speed = task.pos.Normalized() * linearSpeed;
        } else if (const std::shared_ptr<GameObject> gunObject = gun.lock()) {
            if (Gun* gunComponent = gunObject->GetComponent<Gun>()) {
                gunComponent->Shoot(task.pos);
            }
        }
    }

    associated.box += speed * dt;
    if (speed.x != 0.0f) facingLeft = speed.x < 0.0f;

    Animator* animator = associated.GetComponent<Animator>();
    if (hp <= 0) {
        if (animator != nullptr) animator->SetAnimation("dead");
        deathTimer.Update(dt);
        if (deathTimer.Get() > DEATH_DURATION) {
            associated.RequestDelete();
        }
    } else if (animator != nullptr) {
        const bool moving = speed.x != 0.0f || speed.y != 0.0f;
        const std::string name = moving ? "walking" : "idle";
        animator->SetAnimation(facingLeft ? name + "Left" : name);
    }
}

void Character::Render() {}

void Character::Issue(Command task) {
    taskQueue.push(task);
}

#include "Zombie.h"

#include "Animation.h"
#include "Animator.h"
#include "GameObject.h"
#include "SpriteRenderer.h"

Zombie::Zombie(GameObject& associated) : Component(associated), hitpoints(100) {
    auto* renderer = new SpriteRenderer(associated, "img/Enemy.png", 3, 2);
    associated.AddComponent(renderer);

    auto* animator = new Animator(associated);
    animator->AddAnimation("walking", Animation(0, 3, 10.0f));
    animator->AddAnimation("dead", Animation(5, 5, 0.0f));
    animator->SetAnimation("walking");
    associated.AddComponent(animator);
}

void Zombie::Damage(int damage) {
    hitpoints -= damage;
    if (hitpoints <= 0) {
        if (Animator* animator = associated.GetComponent<Animator>()) {
            animator->SetAnimation("dead");
        }
    }
}

void Zombie::Update(float) {
    Damage(1);
}

void Zombie::Render() {}

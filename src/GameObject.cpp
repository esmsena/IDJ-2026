#include "GameObject.h"

GameObject::GameObject() : box(), isDead(false) {}

GameObject::~GameObject() {
    for (auto iterator = components.rbegin(); iterator != components.rend(); ++iterator) {
        delete *iterator;
    }
    components.clear();
}

void GameObject::Update(float dt) {
    for (Component* component : components) {
        component->Update(dt);
    }
}

void GameObject::Render() {
    for (Component* component : components) {
        component->Render();
    }
}

bool GameObject::IsDead() const {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component* component) {
    components.emplace_back(component);
}

void GameObject::RemoveComponent(Component* component) {
    const auto iterator = std::find(components.begin(), components.end(), component);
    if (iterator != components.end()) {
        delete *iterator;
        components.erase(iterator);
    }
}

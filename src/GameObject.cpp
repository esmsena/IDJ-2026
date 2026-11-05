#include "GameObject.h"

GameObject::GameObject()
    : box(), angleDeg(0.0), started(false), z(0), ySortOffset(0.0f), isDead(false) {}

GameObject::~GameObject() {
    for (auto iterator = components.rbegin(); iterator != components.rend(); ++iterator) {
        delete *iterator;
    }
    components.clear();
}

void GameObject::Start() {
    for (std::size_t index = 0; index < components.size(); ++index) {
        components[index]->Start();
    }
    started = true;
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

float GameObject::GetSortY() const {
    return box.y + box.h + ySortOffset;
}

bool GameObject::IsDead() const {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component* component) {
    components.emplace_back(component);
    if (started) {
        component->Start();
    }
}

void GameObject::RemoveComponent(Component* component) {
    const auto iterator = std::find(components.begin(), components.end(), component);
    if (iterator != components.end()) {
        delete *iterator;
        components.erase(iterator);
    }
}

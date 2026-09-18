#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <algorithm>
#include <vector>

#include "Component.h"
#include "Rect.h"

class GameObject {
public:
    GameObject();
    ~GameObject();

    void Update(float dt);
    void Render();
    bool IsDead() const;
    void RequestDelete();
    void AddComponent(Component* component);
    void RemoveComponent(Component* component);

    template <typename T>
    T* GetComponent() const {
        for (Component* component : components) {
            if (T* found = dynamic_cast<T*>(component)) {
                return found;
            }
        }
        return nullptr;
    }

    Rect box;

private:
    std::vector<Component*> components;
    bool isDead;
};

#endif

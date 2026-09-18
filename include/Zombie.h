#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Component.h"

class Zombie : public Component {
public:
    explicit Zombie(GameObject& associated);

    void Damage(int damage);
    void Update(float dt) override;
    void Render() override;

private:
    int hitpoints;
};

#endif

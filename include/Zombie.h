#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Component.h"
#include "Sound.h"

class Zombie : public Component {
public:
    explicit Zombie(GameObject& associated, int hitpoints = 100);

    void Damage(int damage);
    void Update(float dt) override;
    void Render() override;

private:
    int hitpoints;
    Sound deathSound;
};

#endif

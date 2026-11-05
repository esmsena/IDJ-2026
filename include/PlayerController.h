#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "Component.h"

class PlayerController : public Component {
public:
    explicit PlayerController(GameObject& associated);

    void Start() override;
    void Update(float dt) override;
    void Render() override;
};

#endif

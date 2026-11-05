#include "PlayerController.h"

#include "Camera.h"
#include "Character.h"
#include "GameObject.h"
#include "InputManager.h"

PlayerController::PlayerController(GameObject& associated) : Component(associated) {}

void PlayerController::Start() {
    Character::player = associated.GetComponent<Character>();
}

void PlayerController::Update(float) {
    Character* character = associated.GetComponent<Character>();
    if (character == nullptr) {
        return;
    }

    InputManager& input = InputManager::GetInstance();
    Vec2 direction;
    if (input.IsKeyDown(W_KEY)) direction.y -= 1.0f;
    if (input.IsKeyDown(S_KEY)) direction.y += 1.0f;
    if (input.IsKeyDown(A_KEY)) direction.x -= 1.0f;
    if (input.IsKeyDown(D_KEY)) direction.x += 1.0f;

    if (direction.x != 0.0f || direction.y != 0.0f) {
        character->Issue(Character::Command(Character::Command::MOVE, direction.x, direction.y));
    }

    if (input.MousePress(LEFT_MOUSE_BUTTON)) {
        character->Issue(Character::Command(Character::Command::SHOOT,
                                            input.GetMouseX() + Camera::pos.x,
                                            input.GetMouseY() + Camera::pos.y));
    }
}

void PlayerController::Render() {}

#include "Camera.h"

#include "Game.h"
#include "GameObject.h"
#include "InputManager.h"

namespace {
const float CAMERA_SPEED = 400.0f;
}

Vec2 Camera::pos;
Vec2 Camera::speed;
GameObject* Camera::focus = nullptr;

void Camera::Follow(GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(float dt) {
    if (focus != nullptr) {
        int screenWidth = 0;
        int screenHeight = 0;
        SDL_GetRendererOutputSize(Game::GetInstance().GetRenderer(), &screenWidth, &screenHeight);
        pos = focus->box.GetCenter() - Vec2(screenWidth / 2.0f, screenHeight / 2.0f);
        return;
    }

    InputManager& input = InputManager::GetInstance();
    Vec2 direction;
    if (input.IsKeyDown(LEFT_ARROW_KEY)) direction.x -= 1.0f;
    if (input.IsKeyDown(RIGHT_ARROW_KEY)) direction.x += 1.0f;
    if (input.IsKeyDown(UP_ARROW_KEY)) direction.y -= 1.0f;
    if (input.IsKeyDown(DOWN_ARROW_KEY)) direction.y += 1.0f;

    speed = direction.Normalized() * CAMERA_SPEED * dt;
    pos += speed;
}

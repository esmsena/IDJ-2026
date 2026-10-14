#include "InputManager.h"

InputManager& InputManager::GetInstance() {
    static InputManager instance;
    return instance;
}

InputManager::InputManager()
    : mouseState{}, mouseUpdate{}, quitRequested(false), updateCounter(0),
      mouseX(0), mouseY(0) {}

InputManager::~InputManager() = default;

void InputManager::Update() {
    SDL_GetMouseState(&mouseX, &mouseY);
    quitRequested = false;
    ++updateCounter;

    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
        case SDL_QUIT:
            quitRequested = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP: {
            const int button = event.button.button;
            if (button >= 0 && button < 6) {
                mouseState[button] = event.type == SDL_MOUSEBUTTONDOWN;
                mouseUpdate[button] = updateCounter;
            }
            break;
        }
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            if (event.key.repeat == 1) break;
            keyState[event.key.keysym.sym] = event.type == SDL_KEYDOWN;
            keyUpdate[event.key.keysym.sym] = updateCounter;
            break;
        default:
            break;
        }
    }
}

bool InputManager::KeyPress(int key) {
    return keyState[key] && keyUpdate[key] == updateCounter;
}

bool InputManager::KeyRelease(int key) {
    return !keyState[key] && keyUpdate[key] == updateCounter;
}

bool InputManager::IsKeyDown(int key) {
    return keyState[key];
}

bool InputManager::MousePress(int button) const {
    return mouseState[button] && mouseUpdate[button] == updateCounter;
}

bool InputManager::MouseRelease(int button) const {
    return !mouseState[button] && mouseUpdate[button] == updateCounter;
}

bool InputManager::IsMouseDown(int button) const {
    return mouseState[button];
}

int InputManager::GetMouseX() const { return mouseX; }
int InputManager::GetMouseY() const { return mouseY; }

bool InputManager::QuitRequested() const { return quitRequested; }

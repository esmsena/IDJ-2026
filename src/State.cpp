#include "State.h"

#include "Camera.h"
#include "GameObject.h"
#include "InputManager.h"
#include "SpriteRenderer.h"
#include "TileMap.h"
#include "TileSet.h"
#include "Zombie.h"

State::State() : music(), quitRequested(false) {
    LoadAssets();
}

void State::LoadAssets() {
    music.Open("audio/BGM.wav");
    music.Play(-1);

    auto* background = new GameObject();
    auto* backgroundRenderer = new SpriteRenderer(*background, "img/Background.png");
    backgroundRenderer->SetCameraFollower(true);
    background->AddComponent(backgroundRenderer);
    AddObject(background);

    auto* map = new GameObject();
    map->AddComponent(new TileMap(*map, "map/map.txt",
                                  new TileSet(64, 64, "img/Tileset.png")));
    AddObject(map);
}

State::~State() {
    objectArray.clear();
}

void State::Update(float dt) {
    InputManager& input = InputManager::GetInstance();
    if (input.KeyPress(ESCAPE_KEY) || input.QuitRequested()) {
        quitRequested = true;
    }

    Camera::Update(dt);

    if (input.KeyPress(SPACE_KEY)) {
        auto* zombie = new GameObject();
        zombie->AddComponent(new Zombie(*zombie));
        zombie->box.x = input.GetMouseX() + Camera::pos.x - zombie->box.w / 2.0f;
        zombie->box.y = input.GetMouseY() + Camera::pos.y - zombie->box.h / 2.0f;
        AddObject(zombie);
    }

    for (std::size_t index = 0; index < objectArray.size(); ++index) {
        objectArray[index]->Update(dt);
    }

    for (std::size_t index = 0; index < objectArray.size();) {
        if (objectArray[index]->IsDead()) {
            objectArray.erase(objectArray.begin() + static_cast<long>(index));
        } else {
            ++index;
        }
    }
}

void State::Render() const {
    for (const auto& object : objectArray) {
        object->Render();
    }
}

bool State::QuitRequested() const {
    return quitRequested;
}

void State::AddObject(GameObject* gameObject) {
    objectArray.emplace_back(gameObject);
}

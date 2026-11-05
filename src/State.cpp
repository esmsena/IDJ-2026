#include "State.h"

#include <algorithm>

#include "Camera.h"
#include "Character.h"
#include "GameObject.h"
#include "InputManager.h"
#include "PlayerController.h"
#include "SpriteRenderer.h"
#include "TileMap.h"
#include "TileSet.h"
#include "Zombie.h"

namespace {
const int BACKGROUND_Z = -2;
const int MAP_Z = -1;
}

State::State() : music(), quitRequested(false), started(false) {
    auto* background = new GameObject();
    auto* backgroundRenderer = new SpriteRenderer(*background, "img/Background.png");
    backgroundRenderer->SetCameraFollower(true);
    background->AddComponent(backgroundRenderer);
    background->z = BACKGROUND_Z;
    AddObject(background);

    auto* map = new GameObject();
    map->AddComponent(new TileMap(*map, "map/map.txt",
                                  new TileSet(64, 64, "img/Tileset.png")));
    map->z = MAP_Z;
    AddObject(map);

    auto* character = new GameObject();
    character->AddComponent(new Character(*character, "img/Player.png"));
    character->AddComponent(new PlayerController(*character));
    character->box.x = 1280.0f;
    character->box.y = 1280.0f;
    AddObject(character);
    Camera::Follow(character);
}

void State::Start() {
    LoadAssets();

    for (std::size_t index = 0; index < objectArray.size(); ++index) {
        objectArray[index]->Start();
    }
    started = true;
}

void State::LoadAssets() {
    music.Open("audio/BGM.wav");
    music.Play(-1);
}

State::~State() {
    objectArray.clear();
}

void State::Update(float dt) {
    InputManager& input = InputManager::GetInstance();
    if (input.KeyPress(ESCAPE_KEY) || input.QuitRequested()) {
        quitRequested = true;
    }

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

    Camera::Update(dt);

    for (std::size_t index = 0; index < objectArray.size();) {
        if (objectArray[index]->IsDead()) {
            objectArray.erase(objectArray.begin() + static_cast<long>(index));
        } else {
            ++index;
        }
    }
}

void State::Render() const {
    std::vector<GameObject*> renderOrder;
    renderOrder.reserve(objectArray.size());
    for (const auto& object : objectArray) {
        renderOrder.push_back(object.get());
    }

    // Quem esta mais abaixo na tela fica na frente; z separa fundo e mapa do resto.
    std::stable_sort(renderOrder.begin(), renderOrder.end(),
                     [](const GameObject* first, const GameObject* second) {
                         if (first->z != second->z) return first->z < second->z;
                         return first->GetSortY() < second->GetSortY();
                     });

    for (GameObject* object : renderOrder) {
        object->Render();
    }
}

bool State::QuitRequested() const {
    return quitRequested;
}

std::weak_ptr<GameObject> State::AddObject(GameObject* gameObject) {
    std::shared_ptr<GameObject> object(gameObject);
    objectArray.push_back(object);
    if (started) {
        object->Start();
    }
    return std::weak_ptr<GameObject>(object);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* gameObject) {
    for (const auto& object : objectArray) {
        if (object.get() == gameObject) {
            return std::weak_ptr<GameObject>(object);
        }
    }
    return std::weak_ptr<GameObject>();
}

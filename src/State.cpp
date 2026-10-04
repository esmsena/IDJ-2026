#include "State.h"

#include "GameObject.h"
#include "SpriteRenderer.h"
#include "TileMap.h"
#include "TileSet.h"
#include "Vec2.h"
#include "Zombie.h"

State::State() : music(), quitRequested(false) {
    LoadAssets();
}

void State::LoadAssets() {
    music.Open("audio/BGM.wav");
    music.Play(-1);

    auto* background = new GameObject();
    background->AddComponent(new SpriteRenderer(*background, "img/Background.png"));
    AddObject(background);

    auto* map = new GameObject();
    map->AddComponent(new TileMap(*map, "map/map.txt",
                                  new TileSet(64, 64, "img/Tileset.png")));
    AddObject(map);

    const struct {
        Vec2 position;
        int hitpoints;
    } zombies[] = {
        {{600.0f, 450.0f}, 100},
        {{200.0f, 250.0f}, 150},
        {{950.0f, 200.0f}, 200},
        {{350.0f, 700.0f}, 250},
        {{900.0f, 680.0f}, 300},
    };
    for (const auto& data : zombies) {
        auto* zombie = new GameObject();
        zombie->AddComponent(new Zombie(*zombie, data.hitpoints));
        zombie->box.x = data.position.x;
        zombie->box.y = data.position.y;
        AddObject(zombie);
    }
}

State::~State() {
    objectArray.clear();
}

void State::Update(float dt) {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            quitRequested = true;
        }
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

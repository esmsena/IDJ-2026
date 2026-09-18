#include "State.h"

#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Zombie.h"

State::State()
    : music(new Music("audio/BGM.wav")),
      quitRequested(false) {
    music->Play(-1);

    auto* background = new GameObject();
    background->AddComponent(new SpriteRenderer(*background, "img/Background.png"));
    AddObject(background);

    auto* zombie = new GameObject();
    zombie->AddComponent(new Zombie(*zombie));
    zombie->box.x = 600.0f;
    zombie->box.y = 450.0f;
    AddObject(zombie);
}

State::~State() {
    objectArray.clear();
    delete music;
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

#include "State.h"

State::State()
    : bg(new Sprite("img/Background.png")),
      music(new Music("audio/BGM.wav")),
      quitRequested(false) {
    music->Play(-1);
}

State::~State() {
    delete bg;
    delete music;
}

void State::Update(float) {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            quitRequested = true;
        }
    }
}

void State::Render() const {
    bg->Render(0, 0);
}

bool State::QuitRequested() const {
    return quitRequested;
}

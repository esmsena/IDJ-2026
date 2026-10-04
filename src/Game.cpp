#include "Game.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "State.h"
#include "Resources.h"

Game* Game::instance = nullptr;

Game& Game::GetInstance(const std::string& title, int width, int height) {
    if (instance == nullptr) {
        instance = new Game(title, width, height);
        std::atexit([]() {
            delete instance;
            instance = nullptr;
        });
    }

    return *instance;
}

Game::Game(const std::string& title, int width, int height)
    : window(nullptr), renderer(nullptr), state(nullptr) {
    if (instance != nullptr) {
        throw std::logic_error("Ja existe uma instancia de Game em execucao.");
    }
    instance = this;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        throw std::runtime_error(std::string("Erro ao iniciar SDL: ") + SDL_GetError());
    }

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        throw std::runtime_error(std::string("Erro ao iniciar SDL_image: ") + IMG_GetError());
    }

    const int mixFlags = MIX_INIT_OGG | MIX_INIT_MP3;
    if ((Mix_Init(mixFlags) & mixFlags) != mixFlags) {
        std::cerr << "Aviso: nem todos os decoders da SDL_mixer foram carregados: "
                  << Mix_GetError() << '\n';
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
        throw std::runtime_error(std::string("Erro ao iniciar SDL_mixer: ") + Mix_GetError());
    }
    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (window == nullptr) {
        throw std::runtime_error(std::string("Erro ao criar janela: ") + SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        renderer = SDL_CreateRenderer(window, -1, 0);
    }
    if (renderer == nullptr) {
        throw std::runtime_error(std::string("Erro ao criar renderizador: ") + SDL_GetError());
    }

    state = new State();
}

Game::~Game() {
    delete state;
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Renderer* Game::GetRenderer() const {
    return renderer;
}

State& Game::GetState() const {
    return *state;
}

void Game::Run() {
    while (!state->QuitRequested()) {
        state->Update(1.0f / 30.0f);
        SDL_RenderClear(renderer);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }

    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
}

#ifndef GAME_H
#define GAME_H

#include <string>

#include "SDL_include.h"

class State;

class Game {
public:
    static Game& GetInstance(const std::string& title = "IDJ - Nome e Matricula",
                             int width = 1200, int height = 900);
    ~Game();

    SDL_Renderer* GetRenderer() const;
    void Run();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

private:
    Game(const std::string& title, int width, int height);

    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;
};

#endif

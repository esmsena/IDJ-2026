#include <exception>
#include <iostream>

#include "Game.h"

int main(int, char**) {
    try {
        Game& game = Game::GetInstance("Esther Sena Martins- 211062769", 1200, 900);
        game.Run();
    } catch (const std::exception& exception) {
        std::cerr << exception.what() << '\n';
        return 1;
    }

    return 0;
}

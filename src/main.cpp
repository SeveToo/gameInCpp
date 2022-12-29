#include <SFML/Graphics.hpp>
#include "Game.h"

// using namespace sf;

int main() {
    // initialize random seed
    srand(static_cast<unsigned>(time(0)));
    assets();
    // initialize game object
    Game game;

    // game loop
    while (game.running()) {
        game.update();
        game.render();
    }

// end of application
    return 0;
}
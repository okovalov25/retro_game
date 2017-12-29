
#include "ClassGame.hpp"

int main(void) {
    Game game;
    while (!game.getExit())
        game.run();
    return (0);
}
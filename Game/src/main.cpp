#include "Game/Game.h"
#include <iostream>

int main() {
    Game* game = new Game();
    if (game) {
        game->Init();
        game->End();
        delete game;
    }
	return 0;
}
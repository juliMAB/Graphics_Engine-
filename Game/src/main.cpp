#include "Game/Game.h"

int main() {
    Game* game = new Game();

    game->Init();

    while (game->isRunning())
    {
        game->Update();

        game->Draw();
    }

    //if game is not null, then it will be deleted.
    if (game != nullptr) 
    {
        game->Deinit();
        delete game;
    }
	return 0;
}


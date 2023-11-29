#include "Game/Game.h"

int main() {
    int returnValue = 0;

    Game* game = new Game();

    returnValue = game->Init();

    if (returnValue != 0)
        return returnValue;
    

    while (game->IsRunning())
    {
        game->Update();

        game->Draw();
    }

    //if game is not null, then it will be deleted.
    if (game != nullptr) 
    {
        returnValue = game->Deinit();
        if (returnValue != 0)
            return returnValue;
        delete game;
    }
	return returnValue;
}


#include "Game/Game.h"
#include <iostream>
int main(void) {
	Game* g = new Game();
	if (g) {
		g->Start();
		g->Play();
		g->End();
		delete g;
	}
}
#include "Game/Game.h"
#include <iostream>

int main() {
	Game* g = new Game();
	if (g) {
		g->Play();
		delete g;		
	}	
	return 0;
}
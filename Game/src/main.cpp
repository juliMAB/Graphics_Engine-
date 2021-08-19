#include "Game/Game.h"
using namespace Graficos1;
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
#ifndef GAME_H
#define GAME_H
#include "BaseGame/BaseGame.h"

class Game : BaseGame {

public:
	Game();
	~Game();
	void Init();
	void Play();
	void End();
};
#endif
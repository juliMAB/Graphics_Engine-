#ifndef GAME_H
#define GAME_H
#include "BaseGame/BaseGame.h"

class Game : BaseGame {
	const int wt = 960;
	const int ht = 540;
public:
	bool isRunning() {return BaseGame::IsRunning(); };
	Game();
	~Game();
	void Init();
	void Deinit();
	void Update();
	void Draw();
};
#endif
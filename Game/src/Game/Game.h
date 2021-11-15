#ifndef GAME_H
#define GAME_H
#include "BaseGame/BaseGame.h"

class Game : BaseGame {
	Shape* _shape;
	Shape* _shape2;
public:
	Game();
	~Game();
	void Init() override;
	void Deinit() override;
	void Update() override;
	void Draw() override;
};
#endif
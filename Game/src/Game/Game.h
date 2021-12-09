#ifndef GAME_H
#define GAME_H
#include "BaseGame/BaseGame.h"

class Game : BaseGame {
	Shape* _shape;
	Sprite* _amugus;
	Sprite* _pj;
	Sprite* _pixel;
	Sprite* _box;
	Input* input;

public:
	Game();
	~Game();
	void Init() override;
	void Deinit() override;
	void Update() override;
	void Draw() override;
};
#endif
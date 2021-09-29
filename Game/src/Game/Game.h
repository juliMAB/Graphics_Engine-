#ifndef GAME_H
#define GAME_H
#include "BaseGame/BaseGame.h"

class Game : BaseGame {
	Shape* _shape;
public:
	Game();
	~Game();
	void Init();
	void Start() override;
	void End() override;
	void Update() override;
};
#endif
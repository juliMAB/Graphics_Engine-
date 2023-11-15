#ifndef GAME_H
#define GAME_H
#include "BaseGame/BaseGame.h"

class Game : BaseGame {

	
public:
	Game();
	~Game();
	void Init() override;
	void Deinit() override;
	void Update() override;
	void Draw() override;
	void UpdateImgui() override;
};
#endif
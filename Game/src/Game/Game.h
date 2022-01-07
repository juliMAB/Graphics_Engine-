#ifndef GAME_H
#define GAME_H
#include "BaseGame/BaseGame.h"


class Game : BaseGame {
	Shape* _shape;
	//Sprite* _amugus;
	Sprite* _pj;
	//Sprite* _pixel;
	//Sprite* _box;
	//TileMap* _tilemap;
	Input* input;
	//Tile* _tile;
	Camera* _cam;
	float cameraSpeed = 30.f;
public:
	Game();
	~Game();
	void Init() override;
	void Deinit() override;
	void Update() override;
	void Draw() override;
};
#endif
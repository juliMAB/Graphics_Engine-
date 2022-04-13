#ifndef GAME_H
#define GAME_H
#include "BaseGame/BaseGame.h"


class Game : BaseGame {
	Shape* _shape;
	Sprite* _pj;
	Sprite* _box;
	Sprite* _box1;
	Input* input;
	Camera* _cam;
	Shape* _cubeLight;
	float cameraSpeed = 30.f;
	Material* defaultMaterial;
	Shape* _spotCubeLight;
public:
	Game();
	~Game();
	void Init() override;
	void Deinit() override;
	void Update() override;
	void Draw() override;

	void processInput();

};
#endif
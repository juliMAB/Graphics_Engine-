#ifndef GAME_H
#define GAME_H
#include "BaseGame/BaseGame.h"


class Game : BaseGame {
	Shape* _shapes[3];
	Shape* _pj;
	Camera* _cam;
	float cameraSpeed = 30.f;
	Material* defaultMaterial;
	Light* _potatoLight;
public:
	Game();
	~Game();
	void Init() override;
	void Deinit() override;
	void Update() override;
	void Draw() override;

	void processInput();

	void UpdateCameraType();

};
#endif
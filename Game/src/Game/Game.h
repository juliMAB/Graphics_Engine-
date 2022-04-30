#ifndef GAME_H
#define GAME_H
#include "BaseGame/BaseGame.h"


	const int quantity= 20;
class Game : BaseGame {
	Shape* _shapes[quantity];
	Shape* _pj;
	Sprite* _pjS;
	Camera* _cam;
	float cameraSpeed = 30.f;
	Material* _materials[3];
	Shape* _floor;
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
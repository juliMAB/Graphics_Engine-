#ifndef GAME_H
#define GAME_H
#include "BaseGame/BaseGame.h"


	const int quantity= 20;
class Game : BaseGame {
	Sprite* _sprites[quantity];
	Shape* _pj;
	Sprite* _pjS;
	Camera* _cam;
	float cameraSpeed = 30.f;
	Material* _materials[3];
	Shape* _floor;
	Light* _potatoLight;
	Texture* _tex;
	Texture* _tex2;
	
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
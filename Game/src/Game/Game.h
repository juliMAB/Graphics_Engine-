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
	//SpotLight* _potatoLight;
	Texture* _tex;
	Texture* _tex2;
	DirectionLight* _dirLight;
	PointLight* _pointLight[4];
	SpotLight* _spotLight;
	
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
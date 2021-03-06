#ifndef GAME_H
#define GAME_H
#include "BaseGame/BaseGame.h"
//#include "Model/Model.h"

	const int quantity= 20;
	using namespace JuliEngine;
class Game : BaseGame {
	//Sprite* _sprites[quantity];
	//Shape* _pj;
	//Sprite* _pjS;
	Entity2* _a;
	Entity3D* _modeltest;
	Camera2* _cam;
	float cameraSpeed = 30.f;
	//Material* _materials[3];
	Sprite* _floor;
	MyTexture* _tex;
	MyTexture* _tex2;
	DirectionLight* _dirLight;
	PointLight* _pointLight[4];
	SpotLight* _spotLight;
	Shape* _lightcubes[4];
	//bool show_window = true;
	
public:
	Game();
	~Game();
	void Init() override;
	void Deinit() override;
	void Update() override;
	void Draw() override;
	void UpdateImgui() override;

	void LightsUpdate();

	void processInput();

	void UpdateCameraType();

};
#endif
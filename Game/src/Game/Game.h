#ifndef GAME_H
#define GAME_H
#include "BaseGame/BaseGame.h"
//#include "Model/Model.h"

	const int quantity= 20;
	//using namespace JuliEngine;
class Game : BaseGame {
	//Sprite* _sprites[quantity];
	//Shape* _pj;
	//Sprite* _pjS;
	Sprite* _Wall1;
	JuliEngine::Entity2* _a;
<<<<<<< Updated upstream
	JuliEngine::Entity3D* _entity3d;
	JuliEngine::Entity3D* _entity3d2;
	JuliEngine::Model* _modeltest;
=======
	JuliEngine::Entity2* _b;
	list< JuliEngine::Entity2*> planos;
	list< JuliEngine::Entity2*> tankesitos;
	//JuliEngine::Entity3D* _entity3d;
	JuliEngine::Entity3D* _entity3dScene;
	JuliEngine::Model* _modeloTanke;
>>>>>>> Stashed changes
	JuliEngine::Model* _modeltest2;
	JuliEngine::Camera2* _cam;
	JuliEngine::plane* _planeXample;
	Sprite* _floor;
	MyTexture* _tex;
	MyTexture* _tex2;
	JuliEngine::DirectionLight* _dirLight;
	JuliEngine::PointLight* _pointLight[4];
	JuliEngine::SpotLight* _spotLight;
	Shape* _lightcubes[4];

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
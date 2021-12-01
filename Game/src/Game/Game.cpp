#include "Game.h"

float rotation = 0;
float rotationForce = 2;

float position = 0;
float movForce = 0.5f;

glm::vec3 scale = { 1, 1, 1 };
float scaleForce = 0.2f;
float scale1=0;
bool auxCheck = false;

Game::Game() { StartEngine(960, 540, "In Lovyng"); }
Game::~Game() {}
void Game::Init() {
	_shape = new Shape(GetRenderer(), TypeShape::Quad);
	_shape->SetColor(1, 0, 0, 1);
	backgroundColor = { 0.5f,0.5f,0.5f,1 };
	//_sprite = new Sprite(GetRenderer(), "res/c.png");
	_pj = new Sprite(GetRenderer(), "res/d.png");
	_pj->SetPos(0.0f, 0.0f, 0.0f);
	_pj->SetScale(10.0f, 10.0f, 1.0f);
	//_pj->StartUseAnimation();
	_pj->AddAnimation(4, 8, 6.0f,ORDER::RIGHTtoLEFT);
}

void Game::Deinit() {
	if (_shape != nullptr) {
		delete _shape;
		_shape = nullptr;
	}
	if (_sprite != nullptr) {
		delete _sprite;
		_sprite = nullptr;
	}
	std::cout << "\n\nEnd.\n\n";
}
void Game::Update()
{	
	_pj->UpdateAnimation(_time->_deltaTime);
	if (Input::IsKeyRelease(Input::KEY_G))
	{
		scale1 += scaleForce;
		_pj->SetScale(scale1);
		std::cout <<"Time: " << _time->_deltaTime << std::endl;
	}
}
void Game::Draw() {
	//_sprite->Draw();
	_pj->Draw();
	//_shape->Draw();
}
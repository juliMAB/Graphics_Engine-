#include "Game.h"


float rotation = 0;
float rotationForce = 2;

float position = 0;
float movForce = 2.5f;

glm::vec3 scale = { 1, 1, 1 };
float scaleForce = 0.2f;
float scale1=0;
bool auxCheck = false;
enum DIR
{
	DOWN,
	LEFT,
	RIGHT,
	UP,
};
int Down,Left,Right,Up;
Game::Game() { StartEngine(960, 540, "In Lovyng"); }
Game::~Game() {}
void Game::Init() {
	backgroundColor = { 0.5f,0.5f,0.5f,1 };
	//_shape = new Shape(GetRenderer(), TypeShape::Quad);
	//_shape->SetColor(1, 0, 0, 1);
	_sprite = new Sprite(GetRenderer(), "res/b.png");
	_sprite->SetPos(5.0f, 0.0f, 0.0f);
	_sprite->SetScale(1.0f, 1.0f, 1.0f);
	_pj = new Sprite(GetRenderer(), "res/d.png");
	_pj->SetPos(0.0f, 0.0f, 0.0f);
	_pj->SetScale(1.0f, 1.0f, 1.0f);
	_pj->StartUseAnimation();
	_pj->SetAnimations(4, 8, 10.0f,ORDER::RIGHTtoLEFT);
	
	for (int i = 0; i < 4; i++)
	{
		//_pj->SetAction(i*8, (i*8)+8);
	}
	//Down = _pj->SetAction(0, 7);
	//Left=_pj->SetAction(8, 15);
	//Right=_pj->SetAction(16,23);
	//Up=_pj->SetAction(24, 31);
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
	//_pj->UpdateAnimation(_time->_deltaTime);
	//Collision::CollisionUpdate(_pj, _sprite);

	if (Input::IsKeyDown(Input::KEY_G))
	{
		std::cout << "Down" << std::endl;
	}
	if (Input::IsKeyPress(Input::KEY_G))
	{
		std::cout << "Press" << std::endl;
	}
	if (Input::IsKeyUp(Input::KEY_G))
	{
		std::cout << "Up" << std::endl;
	}
}
void Game::Draw() {
	_sprite->Draw();
	_pj->Draw();
	//_shape->Draw();
}
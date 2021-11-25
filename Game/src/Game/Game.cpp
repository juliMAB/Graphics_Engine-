#include "Game.h"

float rotation = 0;
float rotationForce = 2;

float position = 0;
float movForce = 0.5f;

glm::vec3 scale = { 1, 1, 1 };
float scaleForce = 0.2f;
bool auxCheck = false;

Game::Game() { StartEngine(960, 540, "In Lovyng"); }
Game::~Game() {}
void Game::Init() {
	_shape = new Shape(GetRenderer(), TypeShape::Quad);
	_shape->SetColor(1, 0, 0, 1);
	backgroundColor = { 0.5f,0.5f,0.5f,1 };
	_sprite = new Sprite(GetRenderer(), "res/c.png");
	//_pj = new Sprite(GetRenderer(), "res/d.png");
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
	
	
}
void Game::Draw() {
	_sprite->Draw();
	//_pj->Draw();
	//_shape->Draw();
}
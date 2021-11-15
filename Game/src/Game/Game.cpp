#include "Game.h"

float rotation = 0;
float rotationForce = 2;

float position = 0;
float movForce = 0.5f;

glm::vec3 scale = { 1, 1, 1 };
float scaleForce = 0.2f;
bool auxCheck = false;

Game::Game() {}
Game::~Game() {}
void Game::Init() {
	StartEngine(960, 540, "In Lovyng");
	auxCheck = true;
	_shape = new Shape(GetRenderer(), TypeShape::Quad);
	_shape->LoadTexture("res/", "c.png");
}

void Game::Deinit() {
	if (_shape != nullptr) {
		delete _shape;
		_shape = nullptr;
	}
	if (_shape2 != nullptr) {
		delete _shape2;
		_shape2 = nullptr;
	}
	std::cout << "\n\nEnd.\n\n";
}
void Game::Update()
{	
	
	
}
void Game::Draw() {
	ClearWindow(0.5f, 0.5f, 0.5f, 1.0f);
	//_shape->DrawShape();
	//_shape2->DrawShape();
}
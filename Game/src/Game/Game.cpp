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
	
	End();
}
void Game::Start() {
	auxCheck = true;
	_shape = new Shape(GetRenderer(), TypeShape::Quad);
	_shape->LoadTexture("res/", "a.png");

	//_shape2 = new Shape(GetRenderer(), TypeShape::Quad);
	//_shape2->LoadTexture("res/", "b.png");
}
void Game::End() {
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
	if (IsKeyRelease(Input::KEY_UP)) {
		_shape->SetPos(_shape->position.x, _shape->position.y + movForce);
	}
	else if (IsKeyRelease(Input::KEY_LEFT)) {
		_shape->SetPos(_shape->position.x + movForce, _shape->position.y);
	}
	else if (IsKeyRelease(Input::KEY_DOWN)) {
		_shape->SetPos(_shape->position.x, _shape->position.y - movForce);
	}
	else if (IsKeyRelease(Input::KEY_RIGHT)) {
		_shape->SetPos(_shape->position.x - movForce, _shape->position.y);
	}

	if (IsKeyRelease(Input::KEY_W)) {
		scale += scaleForce;
	}
	else if (IsKeyRelease(Input::KEY_S)) {
		scale -= scaleForce;
	}
	_shape->SetScale(scale.x, scale.y, scale.z);
	
	if (IsKeyRelease(Input::KEY_A)) {
		rotation += rotationForce;
	}
	else if (IsKeyRelease(Input::KEY_D)) {
		rotation -= rotationForce;
	}
	_shape->SetRotZ(rotation);
	
}
void Game::Draw() {
	ClearWindow(0.5f, 0.5f, 0.5f, 1.0f);
	_shape->DrawShape();
	//_shape2->DrawShape();
}
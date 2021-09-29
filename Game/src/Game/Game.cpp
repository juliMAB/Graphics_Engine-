#include "Game.h"

float rotation = 0;
float rotationForce = 2;
bool auxCheck = false;
Game::Game() {
}
Game::~Game() {
}

void Game::Init() {
	StartEngine(1920/2, 1080/2, "SauronTeAmo");
	End();
}

void Game::Start()
{
	//StartEngine(1920 / 2, 1080 / 2, "SauronTeAmo");
	//End();
}
void Game::End() {
	std::cout << "\n\nEnd.\n\n";
}
void Game::Update()
{
	if (!auxCheck) {
		auxCheck = true;
		_shape = new Shape(GetRenderer());
		_shape->InitShape(TypeShape::Triangle, TypeShader::Colour);
		_shape->SetRotZ(90.0f);
	}
	
	if (IsKeyRelease(Input::KEY_LEFT)) {
		rotation += rotationForce;
	}
	if (IsKeyRelease(Input::KEY_RIGHT)) {
		rotation -= rotationForce;
	}
	if (IsKeyRelease(Input::KEY_A)) {
		rotation += rotationForce;
		// mover a la izq
	}
	if (IsKeyRelease(Input::KEY_D)) {
		rotation -= rotationForce;
		// mover a la der
	}
	_shape->SetRotZ(rotation);
}
void Game::Draw() {
	ClearWindow(0.5f, 0.5f, 0.5f, 1.0f);
	_shape->SetRotZ(rotation);
	_shape->DrawShape();
}
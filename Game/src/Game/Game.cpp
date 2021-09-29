#include "Game.h"

float rotation = 0;
float rotationForce = 2;

float position = 0;
float movForce = 0.5f;

float scale = 1;
float scaleForce = 0.2f;
bool auxCheck = false;

Game::Game() {
}
Game::~Game() {
}
void Game::Init() {
	StartEngine(1920/2, 1080/2, "In Lovyng");
	End();
}
void Game::Start()
{

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
		_shape->SetPos(position, position, position);
		_shape->SetRotZ(rotation);
		_shape->SetScale(scale, scale, scale);
	}
	
	if (IsKeyRelease(Input::KEY_UP)) {
		_shape->SetPos(_shape->transform.position.x, _shape->transform.position.y + movForce, _shape->transform.position.z);
	}
	else if (IsKeyRelease(Input::KEY_LEFT)) {
		_shape->SetPos(_shape->transform.position.x + movForce, _shape->transform.position.y, _shape->transform.position.z);
	}
	else if (IsKeyRelease(Input::KEY_DOWN)) {
		_shape->SetPos(_shape->transform.position.x, _shape->transform.position.y - movForce, _shape->transform.position.z);
	}
	else if (IsKeyRelease(Input::KEY_RIGHT)) {
		_shape->SetPos(_shape->transform.position.x - movForce, _shape->transform.position.y, _shape->transform.position.z);
	}
	
	if (IsKeyRelease(Input::KEY_W)) {
		scale += scaleForce;
	}
	else if (IsKeyRelease(Input::KEY_S)) {
		scale -= scaleForce;
	}
	_shape->SetScale(scale, scale, scale);
	
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
}
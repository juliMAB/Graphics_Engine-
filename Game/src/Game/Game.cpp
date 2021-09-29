#include "Game.h"

Game::Game() {
}
Game::~Game() {
}

void Game::Init() {
	StartEngine(1920/2, 1080/2, "SauronTeAmo");
	//-------------------------------------------
	_shape = new Shape(GetRenderer());
	_shape->InitShape(TypeShape::Triangle, TypeShader::Colour);
	//_shape->SetScale(0.33f, 0.33f, 0.33f);
	//_shape->SetPos(-1.0f, -1, 5);
	//-----------------------------------------
}
void Game::Start()
{
	UpdateEngine();
	
}

void Game::End() {
	Exit();
}
float xd=0;
void Game::Update()
{
	GetWindow()->ClearWindow(xd, xd, xd, 1.0f);
	_shape->DrawShape();
	GetWindow()->SwapBuffers();
}

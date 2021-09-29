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
	//_shape->SetScale(0.1f, 0.1f, 0.1f);
	//_shape->SetPos(-0.2f, -0.2f, 0.0f);
	//_shape->SetRotations(90.0f, 0, 0);
	_shape->SetRotZ(90.0f);

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
	xd += 0.01f;
	std::cout << "debug" << std::endl;
	GetWindow()->ClearWindow(0.5f, 0.5f, 0.5f, 1.0f);
	//_shape->SetRotations(xd, xd, xd);
	//_shape->SetRotX(xd);
	_shape->SetRotZ(xd);
	_shape->DrawShape();
	GetWindow()->SwapBuffers();
}

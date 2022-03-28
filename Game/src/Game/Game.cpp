#include "Game.h"


float rotation = 0;
float rotationForce = 2;

float position = 0;
float movForce = 2.5f;

glm::vec3 scale = { 1, 1, 1 };
float scaleForce = 0.2f;
float scale1=0;
bool auxCheck = false;

float lastX=0;
float lastY=0;
bool firstMouse = true;


//enum DIR
//{
//	DOWN,
//	RIGHT,
//	LEFT,
//	UP
//};
int Down,Left,Right,Up;
Game::Game() { StartEngine(960, 540, "In Lovyng"); }
Game::~Game() {}
void Game::Init() {
	_cam = _mainCamera;
	color::RGB colorfondo("CCFFCC");
	backgroundColor = { colorfondo.r,colorfondo.g,colorfondo.b,1 };

	_box = new Sprite(GetRenderer(),"res/box.png",true);
	_box->SetScale(10.0f);
}

void Game::Deinit() {
	std::cout << "\n\nEnd.\n\n";
}
void Game::Update()
{	
	processInput();
}
void Game::Draw() {
	_box->Draw();
}

void Game::processInput()
{
	if (Input::IsKeyDown(Input::KEY_W))
		_cam->ProcessKeyboard(FORWARD, _time->_deltaTime);
	if (Input::IsKeyDown(Input::KEY_S))
		_cam->ProcessKeyboard(BACKWARD, _time->_deltaTime);
	if (Input::IsKeyDown(Input::KEY_A))
		_cam->ProcessKeyboard(LEFT, _time->_deltaTime);
	if (Input::IsKeyDown(Input::KEY_D))
		_cam->ProcessKeyboard(RIGHT, _time->_deltaTime);
	if (Input::IsKeyDown(Input::KEY_0))
		_cam->debugCamera();
}


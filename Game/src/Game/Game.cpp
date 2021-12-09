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
	RIGHT,
	LEFT,
	UP,
};
int Down,Left,Right,Up;
Game::Game() { StartEngine(960, 540, "In Lovyng"); }
Game::~Game() {}
void Game::Init() {
	backgroundColor = { 0.5f,0.5f,0.5f,1 };
	
	_shape = new Shape(GetRenderer(), TypeShape(32));
	_shape->SetColor(1, 0.5, 0, 1.0f);
	_shape->SetPos(0.0f, 0.0f, 0.0f);
	_shape->SetScale(5.0f, 5.0f, 5.0f);
	_pixel = new Sprite(GetRenderer(), "res/p1.png",false);
	_pixel->SetPos(-5.0f, 0.0f, 0.0f);
	_pixel->SetScale(2.0f);
	_pixel->SetColor(115.0f /255.0f, 155.0f / 255.0f, 208.0f / 255.0f, 0.5f);
	_amugus = new Sprite(GetRenderer(), "res/b.png",true);
	_amugus->SetPos(5.0f, 0.0f, 0.0f);
	_amugus->SetScale(1.0f, 1.0f, 1.0f);

	_box = new Sprite(GetRenderer(), "res/Box.png",true);
	_box->SetPos(-5.0f, 0.0f, 0.0f);
	_box->SetScale(1.0f, 1.0f, 1.0f);
	_box->_moveable = false;
	_box->_hasCollider = true;
	//-----------pj------------------

	_pj = new Sprite(GetRenderer(), "res/d.png",false);
	_pj->SetPos(0.0f, 0.0f, 0.0f);
	_pj->SetScale(1.0f, 1.0f, 1.0f);

	//------anims pj--------------
	Atlas atlaspj = Atlas(8, 4, 0, 0, .1f, 8);
	_pj->AddAnimation(atlaspj, 1.f);

	atlaspj = Atlas(8, 4, 0, 1, .1f, 8);
	_pj->AddAnimation(atlaspj, 1.f);

	atlaspj = Atlas(8, 4, 0, 2, .1f, 8);
	_pj->AddAnimation(atlaspj, 1.f);

	atlaspj = Atlas(8, 4, 0, 3, .1f, 8);
	_pj->AddAnimation(atlaspj, 1.f);
}

void Game::Deinit() {
	if (_shape != nullptr) {
		delete _shape;
		_shape = nullptr;
	}
	if (_amugus != nullptr) {
		delete _amugus;
		_amugus = nullptr;
	}
	std::cout << "\n\nEnd.\n\n";
}
void Game::Update()
{	
	if (Input::IsKeyDown(Input::KEY_ENTER))
	{
		_shape->CrazyFunc();
	}
	if (Input::IsKeyPress(Input::KEY_A))
	{
		_pj->SetPos(_pj->getPos().x + (movForce * _time->_deltaTime), _pj->getPos().y);
		_pj->ChangeAnimation(static_cast<int>(DIR::LEFT));
		_pj->UpdateAnimation2(_time->_deltaTime);
	}
	else if (Input::IsKeyPress(Input::KEY_D))
	{
		_pj->SetPos(_pj->getPos().x - (movForce * _time->_deltaTime), _pj->getPos().y);
		_pj->ChangeAnimation(static_cast<int>(DIR::RIGHT));
		_pj->UpdateAnimation2(_time->_deltaTime);
	}
	else if (Input::IsKeyPress(Input::KEY_W))
	{
		_pj->SetPos(_pj->getPos().x, _pj->getPos().y + (movForce * _time->_deltaTime));
		_pj->ChangeAnimation(static_cast<int>(DIR::UP));
		_pj->UpdateAnimation2(_time->_deltaTime);
	}
	else if (Input::IsKeyPress(Input::KEY_S))
	{
		_pj->SetPos(_pj->getPos().x, _pj->getPos().y - (movForce * _time->_deltaTime));
		_pj->ChangeAnimation(static_cast<int>(DIR::DOWN));
		_pj->UpdateAnimation2(_time->_deltaTime);
	}
	else if (Input::IsKeyDown(Input::KEY_Z))
	{
		_amugus->FlipHorizontal();
	}
	else if (Input::IsKeyDown(Input::KEY_X))
	{
		_amugus->FlipVertical();
	}
	Collision::CollisionUpdate(_pj, _amugus);
	Collision::CollisionUpdate(_pj, _box);
	Collision::CollisionUpdate(_box, _pj);
	Collision::CollisionUpdate(_box, _amugus);
}
void Game::Draw() {
	_box->Draw();
	_amugus->Draw();
	_pj->Draw();
	_pixel->Draw();
	//_shape->Draw();
}
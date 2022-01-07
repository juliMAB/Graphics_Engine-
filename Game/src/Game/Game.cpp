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
	glm::vec3 camStartingPos = { 0, 0, 150 };
	glm::vec3 camLookPos = { 0, 0, 0 };
	glm::vec3 camUpVector = { 0, 1, 0 };
	_cam = new Camera(GetRenderer(), camStartingPos, camLookPos, camUpVector);
	color::RGB colorfondo("CCFFCC");
	backgroundColor = { colorfondo.r,colorfondo.g,colorfondo.b,1 };
	//----------Shape---------------
	//_shape = new Shape(GetRenderer(), TypeShape::Triangle);
	//_shape->SetScale(10.0f);
	//_shape->SetColor(1, 0, 0, 1);
	//----------TileMap-------------
	//_tilemap = new TileMap(GetRenderer());
	//_tilemap->importTileMap("res/mymapa.xml","res/E3.png");
	//_tilemap->setSize(1.0f);
	//-----------pj------------------
	_pj = new Sprite(GetRenderer(), "res/d.png",false);
	_pj->SetPos(0.0f, 0.0f, 0.0f);
	_pj->SetScale(14.0f);
	_pj->_hasCollider = true;
	_pj->_moveable = true;
	//-----------Amogus----------------
	//_amugus = new Sprite(GetRenderer(), "res/b.png", true);
	//_amugus->SetScale(25.0f);
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

	if (_pj != nullptr) {
		_pj->Deinit();
		delete _pj;
		_pj = nullptr;
	}
	//if (_tilemap != nullptr)
	//{
	//	delete _tilemap;
	//	_tilemap = nullptr;
	//}
	std::cout << "\n\nEnd.\n\n";
}
void Game::Update()
{	
	/*if (Input::IsKeyDown(Input::KEY_ENTER))
	{
		_shape->CrazyFunc();
	}*/
	if (Input::IsKeyPress(Input::KEY_A))
	{
		_pj->SetPos(_pj->getPos().x - (movForce * _time->_deltaTime)*_pj->getScale().x, _pj->getPos().y);
		_pj->ChangeAnimation(static_cast<int>(DIR::RIGHT));
		_pj->UpdateAnimation2(_time->_deltaTime);
	}
	else if (Input::IsKeyPress(Input::KEY_D))
	{
		_pj->SetPos(_pj->getPos().x + (movForce * _time->_deltaTime)* _pj->getScale().x, _pj->getPos().y);
		_pj->ChangeAnimation(static_cast<int>(DIR::LEFT));
		_pj->UpdateAnimation2(_time->_deltaTime);
	}
	else if (Input::IsKeyPress(Input::KEY_W))
	{
		_pj->SetPos(_pj->getPos().x, _pj->getPos().y + (movForce * _time->_deltaTime)* _pj->getScale().y);
		_pj->ChangeAnimation(static_cast<int>(DIR::UP));
		_pj->UpdateAnimation2(_time->_deltaTime);
	}
	else if (Input::IsKeyPress(Input::KEY_S))
	{
		_pj->SetPos(_pj->getPos().x, _pj->getPos().y - (movForce * _time->_deltaTime)* _pj->getScale().y);
		_pj->ChangeAnimation(static_cast<int>(DIR::DOWN));
		_pj->UpdateAnimation2(_time->_deltaTime);
	}
	if (Input::IsKeyPress(Input::KEY_LEFT))
	{
		glm::vec3 movement = { _time->_deltaTime * -cameraSpeed, 0, 0 };
		_cam->moveCamera(movement);
	}
	else if (Input::IsKeyPress(Input::KEY_RIGHT))
	{
		glm::vec3 movement = { _time->_deltaTime * cameraSpeed, 0, 0 };
		_cam->moveCamera(movement);
	}
	if (Input::IsKeyPress(Input::KEY_UP))
	{
		glm::vec3 movement = { 0,  _time->_deltaTime * cameraSpeed , 0 };
		_cam->moveCamera(movement);
	}
	else if (Input::IsKeyPress(Input::KEY_DOWN))
	{
		glm::vec3 movement = { 0,  _time->_deltaTime * -cameraSpeed , 0 };
		_cam->moveCamera(movement);
	}
	else if (Input::IsKeyPress(Input::KEY_U))
	{
		glm::vec3 movement = { 0, 0,  _time->_deltaTime * cameraSpeed };
		_cam->moveCamera(movement);
	}
	else if (Input::IsKeyPress(Input::KEY_I))
	{
		glm::vec3 movement = { 0, 0,  _time->_deltaTime * -cameraSpeed };
		_cam->moveCamera(movement);
	}
	//_tilemap->checkCollision(*_pj);
	//_amugus->SetPos(_pj->pivot);
}
void Game::Draw() {
	//_tilemap->draw2(0);
	//_tilemap->draw2(1);
	_pj->Draw();
	//_tilemap->draw2(2);
	//_amugus->Draw();
}
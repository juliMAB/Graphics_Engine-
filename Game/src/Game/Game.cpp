#include "Game.h"


float rotation = 0;
float rotationForce = 2;

float position = 0;
float movForce = 2.5f;
float speed = 2;
glm::vec3 scale = { 1, 1, 1 };
float scaleForce = 0.2f;
float scale1=0;
bool auxCheck = false;
CAMERA_TYPE auxCheck2 = CAMERA_TYPE::FPS;

float lastX=0;
float lastY=0;
bool firstMouse = true;



//MaterialS emerald{ 
//	{0.0215f,	0.1745f, 0.0215f},
//	{0.07568f,	0.61424f,	0.07568f},
//	{0.633f,	0.727811f,	0.633f,},
//0.60f *100
//};
//MaterialS jade{
//	{0.135f,	0.2225f,	0.1575f},
//	{0.54f,	0.89f,	0.63f},
//	{0.316228f,	0.316228f,	0.316228f},
//	1
//};
//MaterialS obsidian{
//	{0.05375f,	0.05f,	0.06625f},
//	{0.18275f,	0.17f,	0.22525f},
//	{0.332741f,	0.328634f, 0.346435f},
//	0.3f
//};
//MaterialS defaultMat{
//	{0.2f, 0.2f, 0.2f},
//	{0.5f, 0.5f, 0.5f},
//	{1.0f, 1.0f, 1.0f},
//	64.f
//};
MaterialS* defaultM;

//enum DIR
//{
//	DOWN,
//	RIGHT,
//	LEFT,
//	UP
//};
int Down,Left,Right,Up;
Game::Game() { 
	StartEngine(960, 540, "In Lovyng");
}
Game::~Game() {}
void Game::Init() {
	_tex = new Texture("res/e.png", false);
	_tex2 = new Texture("res/f.png", false);
	vec3 a = { 1,1,1 };
	defaultM = new MaterialS{ _tex,_tex2,1 };
	_renderer->SetDepth();
	_cam = _mainCamera;
	color::RGBA colorFondoRGBA(glm::vec4(0,0,0,0));
	SetBackGroundColor(colorFondoRGBA);

	_pjS = new Sprite(_renderer);
	_pjS->Init(SPRITE_TYPE::CUBE);
	_pjS->SetPos(5.f, 0.f, 0.f);
	_pjS->SetColor(1, 1, 1, 1);
	

		int x = 0;
		int y = 0;
	for (int i = 0; i < 15; i++)
	{
		_sprites[i] = new Sprite(_renderer);
		_sprites[i]->Init(SPRITE_TYPE::CUBE);
		_sprites[i]->SetPos(2.f, i-y, x);
		_sprites[i]->SetMateria(defaultM);
		if (i == 4 || i == 9 || i == 14)
		{
			x++;
			y += 5;

		}
	}
	//_shapes[10]->SetColor(0.1f, 0.1f, 0.1f, 1);
	//_shapes[11]->SetColor(1, 0, 0, 1);
	//_shapes[12]->SetColor(0, 1, 0, 1);
	//_shapes[13]->SetColor(0, 0, 1, 1);
	//_shapes[14]->SetColor(1, 1, 1, 1);
	_cam->SetTarget(_sprites[0]);
	_cam->SetSensitivity(0.25f);
	_cam->SetOffset(10.f);
	//
	//
	_potatoLight = new Light(_renderer);
	_potatoLight->SetAmbientStrength(1.0f);
	_potatoLight->SetColor(1.0f, 1.0f, 1.0f);
	_potatoLight->SetAmbient(glm::vec3(1.0f, 1.0f, 1.0f));
	_potatoLight->SetDiffuse(glm::vec3(1.0f, 1.0f, 1.0f));
	_potatoLight->SetSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
	//_potatoLight->SetDirection(glm::vec3(-0.2f, -1.0f, -0.3f));
	//
	//
	//_shapes[2] = new Shape(_renderer);
	//_shapes[2]->Init(SHAPE_TYPE::CUBE);
	//_shapes[2]->SetPos(2.f, 3.f, 0.f);
	//_shapes[2]->SetColor(0, 0, 1.f, 1);
	//
	//_shapes[0]->SetMateria(defaultMat, _renderer);
	//_shapes[1]->SetMateria(defaultMat, _renderer);
	//_shapes[2]->SetMateria(defaultMat, _renderer);
	//_shapes[0]->SetMateria(emerald,_renderer);
	//_shapes[1]->SetMateria(emerald, _renderer);

	Input::lock_cursor(true);
}

void Game::Deinit() {
	std::cout << "-Game";
}
void Game::Update()
{	
	_cam->Update();
	_potatoLight->UpdateLight();
	processInput();
	for (int i = 0; i < 15; i++)
	{
		_sprites[i]->UpdateMaterial();
	}
}
void Game::Draw() {
	//_pjS->Draw();
	//_shapes[0]->Draw();
	//_shapes[1]->Draw();
	//_shapes[2]->Draw();
	//_floor->Draw();
	for (int i = 0; i < 15; i++)
	{
		_sprites[i]->Draw();
	}
}

void Game::processInput()
{
	glm::vec3 a(0);
	float t = _time->_deltaTime * speed;
	if (Input::IsKeyPressed(Input::KEY_W))
		a += vec3(0, 0, t);
	if (Input::IsKeyPressed(Input::KEY_S))
		a += vec3(0, 0, -t);
	if (Input::IsKeyPressed(Input::KEY_A))
		a += vec3(t, 0, 0);
	if (Input::IsKeyPressed(Input::KEY_D))
		a += vec3(-t, 0, 0);
	if (Input::IsKeyPressed(Input::KEY_Q))
		a += vec3(0, t, 0);
	if (Input::IsKeyPressed(Input::KEY_E))
		a += vec3(0, -t, 0);
	if (Input::IsKeyDown(Input::KEY_X))
		_cam->DebugInfo();
	if (Input::IsKeyDown(Input::KEY_C))
		auxCheck = !auxCheck;
	Input::lock_cursor(auxCheck);
	_cam->GetTarget()->SetPos(_cam->GetTarget()->getPos() + a);
	//_pjS->SetPos(_pjS->getPos()+a);
	_potatoLight->SetPos(_cam->GetTarget()->getPos());
	if (Input::IsKeyDown(Input::KEY_B))
		UpdateCameraType();
	_cam->SetCameraType((CAMERA_TYPE)auxCheck2);
	if (Input::IsKeyDown(Input::KEY_SPACE))
	{
	}
}
void Game::UpdateCameraType() {
	int C = (int)auxCheck2;
	C++;
	if (C > (int)CAMERA_TYPE::Max)
	{
		C = 0;
	}

	auxCheck2 = (CAMERA_TYPE)C;
}


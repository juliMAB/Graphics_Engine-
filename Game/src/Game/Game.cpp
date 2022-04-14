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
Game::Game() { 
	StartEngine(960, 540, "In Lovyng");
	_shape = nullptr;

}
Game::~Game() {}
void Game::Init() {
	GetRenderer()->SetDepth();
	_cam = _mainCamera;
	color::RGB colorfondo("CCFFCC");
	color::RGBA colorFondoRGBA(colorfondo);
	SetBackGroundColor(colorFondoRGBA);
	_pj = new Sprite(GetRenderer());
	_pj->Init(SPRITE_TYPE::CUBE);
	_pj->LoadTexture("res/c.jpg", false);
	_pj->SetPos(5.f,0.f,0.f);
	_pj->_color.SetColor(1, 1, 1,.5f);
	
	_cam->SetTarget(_pj);
	_cam->SetSensitivity(0.25f);
	_cam->SetOffset(10.f);
	_cam->SetCameraType(CAMERA_TYPE::TPS);

	_floor = new Sprite(GetRenderer());
	_floor->Init(SPRITE_TYPE::QUAD);
	_floor->LoadTexture("res/p.jpg",false);
	_floor->SetPos(glm::vec3(0));
	_floor->SetScale(50);
	_floor->SetRotX(90);

	_box = new Sprite(GetRenderer());
	_box->Init(SPRITE_TYPE::QUAD);
	_box->LoadTexture("res/Box.png", false);
	_box->SetPos(glm::vec3(0));
	_box->SetScale(50);
	//_box->SetRotX(90);



	_cubeLight = new Shape(GetRenderer());
	_cubeLight->Init(SHAPE_TYPE::CUBE);
	_cubeLight->SetPos(glm::vec3(15.f, 2.5f, 0.f));
	_cubeLight->_color.SetColor(0, 255, 0);

	_spotCubeLight = new Shape(GetRenderer());
	_spotCubeLight->Init(SHAPE_TYPE::CUBE);
	_spotCubeLight->SetPos(glm::vec3(0.f, 5.f, 0.f));
	_spotCubeLight->_color.SetColor(255, 0, 0);
	_spotCubeLight->SetScale(0.75f);

	defaultMaterial = new Material(GetRenderer());
	defaultMaterial->Init();
	defaultMaterial->SetShininess(32.f);
	defaultMaterial->SetAmbient(glm::vec3(0.5f, 0.5f, 0.5f));
	defaultMaterial->SetDiffuse(glm::vec3(0.4f, 0.4f, 0.4f));
	defaultMaterial->SetSpecular(glm::vec3(0.5f, 0.5f, 0.5f));
	defaultMaterial->UpdateShader();

	_lightManager->AddLight(LIGHT_TYPE::DIRECTIONAL);
	DirectionalLight* directionalLight = _lightManager->GetDirectionalLight();
	directionalLight->Init();
	directionalLight->color.SetColor(240, 240, 240);
	directionalLight->SetDirection(glm::vec3(-0.2f, -1.0f, -0.3f));
	directionalLight->SetAmbient(glm::vec3(0.5f, 0.5f, 0.5f));
	directionalLight->SetDiffuse(glm::vec3(0.4f, 0.4f, 0.4f));
	directionalLight->SetSpecular(glm::vec3(0.5f, 0.5f, 0.5f));

	_lightManager->AddLight(LIGHT_TYPE::POINTLIGHT);
	PointLight* pointLight = _lightManager->GetLasPointLightCreated();
	pointLight->SetPos(_cubeLight->getPos() + glm::vec3(0.f, 2.5f, 0.f));
	pointLight->color = _cubeLight->_color;
	pointLight->SetAmbient(glm::vec3(0.05f, 0.05f, 0.05f));
	pointLight->SetDiffuse(glm::vec3(0.8f, 0.8f, 0.8f));
	pointLight->SetSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
	pointLight->SetConstant(1.f);
	pointLight->SetLinear(0.09f);
	pointLight->SetQuadratic(0.032f);

	_lightManager->AddLight(LIGHT_TYPE::SPOTLIGHT);
	SpotLight* spotLight = _lightManager->GetLasSpotLightCreated();
	spotLight->SetPos(_spotCubeLight->getPos());
	spotLight->SetDirection(glm::vec3(0.0f, -1.0f, 0.0f));
	spotLight->color = _spotCubeLight->_color;
	spotLight->SetAmbient(glm::vec3(1.f, 1.f, 1.f));
	spotLight->SetDiffuse(glm::vec3(1.f, 1.f, 1.f));
	spotLight->SetSpecular(glm::vec3(1.f, 1.f, 1.f));
	spotLight->SetConstant(1.f);
	spotLight->SetLinear(0.1f);
	spotLight->SetQuadratic(0.032f);
	spotLight->SetCutOff(25.f);
	spotLight->SetOuterCutOff(15.f);

	Input::lock_cursor(true);
	_cam->SetCameraType(CAMERA_TYPE::TPS);
}

void Game::Deinit() {
	std::cout << "-Game";
}
void Game::Update()
{	
	_cam->Update();
	processInput();
}
void Game::Draw() {
	_cubeLight->Draw();
	_spotCubeLight->Draw();
	_pj->Draw();
	_floor->Draw();
	_box->Draw();
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
	if (Input::IsKeyDown(Input::KEY_0))
		_cam->debugCamera();
	if (Input::IsKeyDown(Input::KEY_C))
		auxCheck = !auxCheck;
		Input::lock_cursor(auxCheck);
		_pj->SetPos(_pj->getPos()+a);
}


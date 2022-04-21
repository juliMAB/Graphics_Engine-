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
	_renderer->SetDepth();
	_cam = _mainCamera;
	color::RGB colorfondo("CCFFCC");
	color::RGBA colorFondoRGBA(colorfondo);
	SetBackGroundColor(colorFondoRGBA);
	_pj = new Shape(_renderer);
	_pj->Init(SHAPE_TYPE::CUBE);
	_pj->SetPos(5.f,0.f,0.f);
	_pj->_color.SetColor(1, 0, 0, 1);
	
	_cam->SetTarget(_pj);
	_cam->SetSensitivity(0.25f);
	_cam->SetOffset(10.f);
	_cam->SetCameraType(CAMERA_TYPE::TPS);

	defaultMaterial = new Material(GetRenderer());
	defaultMaterial->Init();
	defaultMaterial->SetShininess(32.f);
	defaultMaterial->SetAmbient(glm::vec3(0.5f, 0.5f, 0.5f));
	defaultMaterial->SetDiffuse(glm::vec3(0.4f, 0.4f, 0.4f));
	defaultMaterial->SetSpecular(glm::vec3(0.5f, 0.5f, 0.5f));
	defaultMaterial->UpdateShader();


	_renderer->SetLight(glm::vec3(1, 0, 0));
	//_lightManager->AddLight(LIGHT_TYPE::DIRECTIONAL);
	//DirectionalLight* directionalLight = _lightManager->GetDirectionalLight();
	//directionalLight->Init();
	//directionalLight->color.SetColor(240, 240, 240);
	//directionalLight->SetDirection(glm::vec3(-0.2f, -1.0f, -0.3f));
	//directionalLight->SetAmbient(glm::vec3(0.5f, 0.5f, 0.5f));
	//directionalLight->SetDiffuse(glm::vec3(0.4f, 0.4f, 0.4f));
	//directionalLight->SetSpecular(glm::vec3(0.5f, 0.5f, 0.5f));

	//_lightManager->AddLight(LIGHT_TYPE::POINTLIGHT);
	//PointLight* pointLight = _lightManager->GetLasPointLightCreated();
	//pointLight->SetPos(_shapes[0]->getPos() + glm::vec3(0.f, 2.5f, 0.f));
	//pointLight->color = _shapes[0]->_color;
	//pointLight->SetAmbient(glm::vec3(0.05f, 0.05f, 0.05f));
	//pointLight->SetDiffuse(glm::vec3(0.8f, 0.8f, 0.8f));
	//pointLight->SetSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
	//pointLight->SetConstant(1.f);
	//pointLight->SetLinear(0.09f);
	//pointLight->SetQuadratic(0.032f);

	/*_lightManager->AddLight(LIGHT_TYPE::SPOTLIGHT);
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
	spotLight->SetOuterCutOff(15.f);*/

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
	_pj->Draw();
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
	if (Input::IsKeyDown(Input::KEY_B))
		UpdateCameraType();
	_cam->SetCameraType((CAMERA_TYPE)auxCheck2);
}
void Game::UpdateCameraType() {
	int C = (int)auxCheck2;
	C++;
	if (C > (int)CAMERA_TYPE::TOP_DOWN)
	{
		C = 0;
	}

	auxCheck2 = (CAMERA_TYPE)C;
}


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




MaterialS* defaultM;

int Down,Left,Right,Up;

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
};
Game::Game() { 
	MainLoop(960, 540, "In Lovyng");
	_a =nullptr;
	_floor				  =nullptr;
	_tex				  =nullptr;
	_tex2				  =nullptr;
	_dirLight			  =nullptr;
	for (int i = 0; i < 4; i++)
		_pointLight[i] = nullptr;
	for (int i = 0; i < 4; i++)
		_lightcubes[i] = nullptr;

	_spotLight	  =nullptr;
	_modeltest	  =nullptr;
}
Game::~Game() {}
void Game::Init() {
	_tex = new MyTexture("res/e.png", false);
	_tex2 = new MyTexture("res/f.png", false);
	vec3 a = { 1,1,1 };
	defaultM = new MaterialS{ _tex,_tex2,32.0f };
	_renderer->SetDepth();
	_cam = _mainCamera2;
	color::RGBA colorFondoRGBA(glm::vec4(0,0,0,0));
	SetBackGroundColor(colorFondoRGBA);
	_entity3d = new JuliEngine::Entity3D(_renderer, "res/h/model.obj");
	_entity3d2 = new JuliEngine::Entity3D(_renderer, "res/i/A2.dae");
	_modeltest = _entity3d->model;
	_modeltest2 = _entity3d2->model;
	_entity3d2->model->GetBaseNode()->SetPos(0, 0, 5);
	_modeltest->GetBaseNode()->Init();
	_modeltest2->GetBaseNode()->Init();
	_modeltest->GetBaseNode()->SetPos({0,0,0});
	_modeltest->GetBaseNode()->SetScale({ 1,1,1 });
	_cam->SetSensitivity(0.25f);
	_cam->SetOffset(10.f);
	JuliEngine::OcclusionCulling::Init(_cam);

	//--------FLOOR----------
	_floor = new Sprite(_renderer);
	_floor->Init(SPRITE_TYPE::QUAD);
	_floor->SetMateria(defaultM);
	_floor->SetName("piso");
	_floor->SetPos(0, -5);
	_floor->SetRotations(90, 0,0);
	_floor->SetScale(10);
	//----------------------


	_dirLight = new JuliEngine::DirectionLight(_renderer);
	_dirLight->Init();
	_dirLight->SetDirection(glm::vec3(-0.2f, -1.0f, -0.3f));
	_dirLight->SetAmbient(glm::vec3(0.05f, 0.05f, 0.05f));
	_dirLight->SetDiffuse(glm::vec3(0.4f, 0.4f, 0.4f));
	_dirLight->SetSpecular(glm::vec3(0.5f, 0.5f, 0.5f));

	for (int i = 0; i < 4; i++)
	{
		_pointLight[i] = new JuliEngine::PointLight(_renderer);
		_pointLight[i]->Init();
		_pointLight[i]->SetPos(pointLightPositions[i]);
		_pointLight[i]->SetAmbient(vec3(0.05f, 0.05f, 0.05f));
		_pointLight[i]->SetDiffuse(vec3(0.8f, 0.8f, 0.8f));
		_pointLight[i]->SetSpecular(vec3(1.0f, 1.0f, 1.0f));
		_pointLight[i]->SetConstant(1.0f);
		_pointLight[i]->SetLinear(0.09f);
		_pointLight[i]->SetQuadratic(0.032f);

		_lightcubes[i] = new Shape(_renderer);
		_lightcubes[i]->Init(SHAPE_TYPE::QUAD);
	}
	
	_spotLight = new JuliEngine::SpotLight(_renderer);
	_spotLight->Init();
	_spotLight->SetCamera(_cam);
	_spotLight->SetAmbient(vec3(0.0f, 0.0f, 0.0f));
	_spotLight->SetDiffuse(vec3(1.0f, 1.0f, 1.0f));
	_spotLight->SetSpecular(vec3(1.0f, 1.0f, 1.0f));
	_spotLight->SetConstant(1.0f);
	_spotLight->SetLinear(0.09f);
	_spotLight->SetQuadratic(0.032f);
	_spotLight->SetCutOff(glm::cos(glm::radians(12.5f)));
	_spotLight->SetOuterCutOff(glm::cos(glm::radians(15.0f)));

	_cam->SetCameraType(JuliEngine::CAMERA_TYPE::FC);
	_cam->SetPos(vec3(0.0f, 0.0f, 10.0f));

	_cam->ToogleEjes();
}

void Game::Deinit() {
	std::cout << "-Game";
}
void Game::Update()
{	
	for (int i = 0; i < 4; i++)
		_lightcubes[i]->SetPos(_pointLight[i]->getPos());
	_cam->Update();
	_floor->UpdateMaterial();
	LightsUpdate();
	processInput();
	JuliEngine::OcclusionCulling::Update();
}
void Game::Draw() {
	_floor->Draw();
	_modeltest->GetBaseNode()->setDraw();
	_modeltest2->GetBaseNode()->setDraw();
	for (int i = 0; i < 4; i++)
		_lightcubes[i]->Draw();
}
void Game::UpdateImgui()
{

}
void Game::LightsUpdate()
{
	_dirLight->UpdateLight();
	for (int i = 0; i < 4; i++)
	{
		_pointLight[i]->UpdateLight();
	}
	_spotLight->UpdateLight();
	_cam->Update();
}
void Game::processInput()
{
	glm::vec3 a(0);
	float t = _time->_deltaTime * speed;

	if (Input::IsKeyPressed(Input::KEY_W))
		a += _cam->GetFront();
	if (Input::IsKeyPressed(Input::KEY_S))
		a -= _cam->GetFront();
	if (Input::IsKeyPressed(Input::KEY_A))
		a -= _cam->GetRight();
	if (Input::IsKeyPressed(Input::KEY_D))
		a += _cam->GetRight();
	if (Input::IsKeyPressed(Input::KEY_Q))
		a -= _cam->GetUp();
	if (Input::IsKeyPressed(Input::KEY_E))
		a += _cam->GetUp();
	if (auxCheck2 == CAMERA_TYPE::FC)
		_cam->Move(a * _time->_deltaTime);

	if (Input::IsKeyDown(Input::KEY_X))
		_cam->DebugInfo();
	if (Input::IsKeyDown(Input::KEY_C))
	{
		auxCheck = !auxCheck;
		Input::lock_cursor(auxCheck);
		if (auxCheck)
			std::cout << "Lock Cursor (ON)" << std::endl;
		else
			std::cout << "Lock Cursor (OFF)" << std::endl;
	}
	if (Input::IsKeyDown(Input::KEY_B))
		UpdateCameraType();
	_cam->SetCameraType((JuliEngine::CAMERA_TYPE)auxCheck2);
	if (Input::IsKeyDown(Input::KEY_SPACE))
		_cam->ToogleEjes();
}
void Game::UpdateCameraType() {
	int C = (int)auxCheck2;
	C++;
	if (C > (int)CAMERA_TYPE::Max)
	{
		C = 0;
	}

	auxCheck2 = (CAMERA_TYPE)C;
	switch (auxCheck2)
	{
	case CAMERA_TYPE::FC:
		std::cout << "Camera:Free Camera" << std::endl;
		break;
	case CAMERA_TYPE::FPS:
		std::cout << "Camera:First Person Shooter" << std::endl;
		break;
	case CAMERA_TYPE::TPS:
		std::cout << "Camera:Three Person Shooter" << std::endl;
		break;
	case CAMERA_TYPE::Max:
		std::cout << "Camera:NONE" << std::endl;
		break;
	default:
		break;

	}
}

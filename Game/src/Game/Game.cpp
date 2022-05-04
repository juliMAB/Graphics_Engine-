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
	StartEngine(960, 540, "In Lovyng");
	for (int i = 0; i < quantity; i++)
		_sprites[i] = nullptr;
	_pj					  =nullptr;
	_pjS				  =nullptr;
	_cam				  =nullptr;
	cameraSpeed			  =30.f;
	for (int i = 0; i < 3; i++)
		_materials[i] = nullptr;
	_floor				  =nullptr;
	_tex				  =nullptr;
	_tex2				  =nullptr;
	_dirLight			  =nullptr;
	for (int i = 0; i < 4; i++)
		_pointLight[i] = nullptr;
	
	_spotLight	  =nullptr;
}
Game::~Game() {}
void Game::Init() {
	_tex = new Texture("res/e.png", false);
	_tex2 = new Texture("res/f.png", false);
	vec3 a = { 1,1,1 };
	defaultM = new MaterialS{ _tex,_tex2,32.0f };
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
		if (i<10)
		{
		_sprites[i]->SetPos(cubePositions[i]);

		}
	}

	_cam->SetTarget(_sprites[0]);
	_cam->SetSensitivity(0.25f);
	_cam->SetOffset(10.f);

	_dirLight = new DirectionLight(_renderer);
	_dirLight->Init();
	_dirLight->SetDirection(glm::vec3(-0.2f, -1.0f, -0.3f));
	_dirLight->SetAmbient(glm::vec3(0.05f, 0.05f, 0.05f));
	_dirLight->SetDiffuse(glm::vec3(0.4f, 0.4f, 0.4f));
	_dirLight->SetSpecular(glm::vec3(0.5f, 0.5f, 0.5f));

	for (int i = 0; i < 4; i++)
	{
		_pointLight[i] = new PointLight(_renderer);
		_pointLight[i]->Init();
		_pointLight[i]->SetPos(pointLightPositions[i]);
		_pointLight[i]->SetAmbient(vec3(0.05f, 0.05f, 0.05f));
		_pointLight[i]->SetDiffuse(vec3(0.8f, 0.8f, 0.8f));
		_pointLight[i]->SetSpecular(vec3(1.0f, 1.0f, 1.0f));
		_pointLight[i]->SetConstant(1.0f);
		_pointLight[i]->SetLinear(0.09f);
		_pointLight[i]->SetQuadratic(0.032f);
	}

	_spotLight = new SpotLight(_renderer);
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


	Input::lock_cursor(true);
}

void Game::Deinit() {
	std::cout << "-Game";
}
void Game::Update()
{	
	_cam->Update();
	LightsUpdate();
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
void Game::LightsUpdate()
{
	_dirLight->UpdateLight();
	for (int i = 0; i < 4; i++)
	{
		_pointLight[i]->UpdateLight();
	}
	_spotLight->UpdateLight();
}
void Game::processInput()
{
	glm::vec3 a(0);
	float t = _time->_deltaTime * speed;

	if (Input::IsKeyPressed(Input::KEY_W))
		a += _cam->GetFront();
	if (Input::IsKeyPressed(Input::KEY_S))
		a += -_cam->GetFront();
	if (Input::IsKeyPressed(Input::KEY_A))
		a += _cam.get;
	if (Input::IsKeyPressed(Input::KEY_D))
		a += vec3(-t, 0, 0);
	if (Input::IsKeyPressed(Input::KEY_Q))
		a += vec3(0, t, 0);
	if (Input::IsKeyPressed(Input::KEY_E))
		a += vec3(0, -t, 0);
	if (auxCheck2 == CAMERA_TYPE::TPS)
		_cam->GetTarget()->SetPos(_cam->GetTarget()->getPos() + a);
	if (auxCheck2 == CAMERA_TYPE::FC)
		_cam->SetPos(_cam->getPos() + a);
	
	if (Input::IsKeyDown(Input::KEY_X))
		_cam->DebugInfo();
	if (Input::IsKeyDown(Input::KEY_C))
		auxCheck = !auxCheck;
	Input::lock_cursor(auxCheck);
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


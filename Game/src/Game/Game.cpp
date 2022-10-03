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
	if (_Wall1!=nullptr)
		_Wall1 = nullptr;
	if (_a					!=nullptr)
		_a					  =nullptr;
<<<<<<< Updated upstream
	if (_floor!=nullptr)
		_floor				  =nullptr;
	if (_tex != nullptr)
		_tex				  =nullptr;
	if (_tex2 != nullptr)
		_tex2				  =nullptr;
=======
	if (_b					!= nullptr)
		_b					= nullptr;
	//if (_floor!=nullptr)
	//	_floor				  =nullptr;
>>>>>>> Stashed changes
	if (_dirLight != nullptr)
		_dirLight			  =nullptr;
	for (int i = 0; i < 4; i++)
		if (_pointLight[i] != nullptr)
			_pointLight[i] = nullptr;
	for (int i = 0; i < 4; i++)
		if (_lightcubes[i] != nullptr)
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
<<<<<<< Updated upstream
	_entity3d = new JuliEngine::Entity3D(_renderer, "res/h/model.obj");
	_entity3d2 = new JuliEngine::Entity3D(_renderer, "res/i/A2.dae");
	_modeltest = _entity3d->model;
	_modeltest2 = _entity3d2->model;
	_entity3d2->model->GetBaseNode()->SetPos(0, 0, 5);
	_modeltest->GetBaseNode()->Init();
	_modeltest2->GetBaseNode()->Init();
	_modeltest->GetBaseNode()->SetPos({0,0,0});
	_modeltest->GetBaseNode()->SetScale({ 1,1,1 });
=======
	//_entity3d = new JuliEngine::Entity3D(_renderer, "res/h/model.obj");
	_entity3dScene = new JuliEngine::Entity3D(_renderer, "res/i/scene.fbx");
	//_entity3d->model->GetBaseNode()->Init();

	JuliEngine::Entity2* wantedPlano1 = _entity3dScene->model->GetBaseNode()->GetNode("bsp_plano1");
	//JuliEngine::Entity2* wantedPlano2 = _entity3dScene->model->GetBaseNode()->GetNode("bsp_plano2");
	//JuliEngine::Entity2* wantedPlano3 = _entity3dScene->model->GetBaseNode()->GetNode("bsp_plano3");
	JuliEngine::Entity2* wantedNode = _entity3dScene->model->GetBaseNode()->GetNode("Tanke");
	//JuliEngine::Entity2* wantedNode1 = _entity3dScene->model->GetBaseNode()->GetNode("Tanke1");
	//JuliEngine::Entity2* wantedNode2 = _entity3dScene->model->GetBaseNode()->GetNode("Tanke2");
	JuliEngine::Entity2* wantedNode3 = _entity3dScene->model->GetBaseNode()->GetNode("Tanke3");

	planos.push_front(wantedPlano1);
	//planos.push_front(wantedPlano2);
	//planos.push_front(wantedPlano3);
	tankesitos.push_front(wantedNode);
	//tankesitos.push_front(wantedNode1);
	//tankesitos.push_front(wantedNode2);
	tankesitos.push_front(wantedNode3);
	if (wantedNode != nullptr)
	{
		_modeloTanke = new JuliEngine::Model(GetRenderer());
		_modeloTanke->SetBaseNode(wantedNode);
	}
	//if (wantedNodeBsp!= nullptr)
	//{
	//	_b = wantedNodeBsp;
	//}

	if (_modeloTanke == nullptr)
	{
		_modeloTanke = _entity3dScene->model;
	}
	_modeloTanke->GetBaseNode()->Init();
>>>>>>> Stashed changes
	_cam->SetSensitivity(0.25f);
	_cam->SetOffset(10.f);
	JuliEngine::OcclusionCulling::Init(_cam);

<<<<<<< Updated upstream
	//--------FLOOR----------
	_floor = new Sprite(_renderer);
	_floor->Init(SPRITE_TYPE::QUAD);
	_floor->SetMateria(defaultM);
	_floor->SetName("piso");
	_floor->SetPos(0, -5);
	_floor->SetRotations(90, 0,0);
	_floor->SetScale(10);
	//----------------------
	//--------WALL----------
	_Wall1 = new Sprite(_renderer);
	_Wall1->Init(SPRITE_TYPE::QUAD);
	_Wall1->SetMateria(defaultM);
	_Wall1->SetName("Wall");
	_Wall1->SetPos(10, 0, 0);
	_Wall1->SetRotations(0, 90, 0);
	_Wall1->SetScale(10);
	//----------------------

=======
>>>>>>> Stashed changes

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

	_bsp = new JuliEngine::BSP(_renderer, _cam);

<<<<<<< Updated upstream


	for (std::list<JuliEngine::Entity2*>::iterator it2 = JuliEngine::Entity2::EntitysLists.begin(); it2 != JuliEngine::Entity2::EntitysLists.end(); ++it2)
	{
		_bsp->AddEntity((*it2));
	}
	vec3 xa = _Wall1->getPos() + vec3(0, 0, 1);
	vec3 xb = _Wall1->getPos() + vec3(0, 0, -1);
	vec3 xc = _Wall1->getPos() + vec3(0, 1, 0);
	_planeXample = new JuliEngine::plane(xa, xb, xc);
	_bsp->AddPlane(_planeXample);
=======
	_a = _cam;

	_renderer->SetBackgroundColor(vec4((float)(255.f/255.f), (float)(192.f/255.f), (float)(203.f/255.f),0.5f));
>>>>>>> Stashed changes
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
	_Wall1->UpdateMaterial();
	LightsUpdate();
	processInput();
	JuliEngine::OcclusionCulling::Update();
}
void Game::Draw() {
<<<<<<< Updated upstream
	_floor->Draw();
	_Wall1->Draw();
	//_modeltest->GetBaseNode()->setDraw();
	//_modeltest2->GetBaseNode()->setDraw();
	_bsp->Draw();
=======
	//_modeloTanke->GetBaseNode()->setDraw();
>>>>>>> Stashed changes
	for (int i = 0; i < 4; i++)
		//_lightcubes[i]->Draw();
	for (std::list<Entity2*>::iterator it = planos.begin(); it != planos.end(); it++)
		if ((*it)!=nullptr)
			(*it)->setDraw();
	for (std::list<Entity2*>::iterator it = tankesitos.begin(); it != tankesitos.end(); it++)
		if ((*it) != nullptr)
			(*it)->setDraw();

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
		a += _cam->GetFront() *t;
	if (Input::IsKeyPressed(Input::KEY_S))
		a -= _cam->GetFront() *t;
	if (Input::IsKeyPressed(Input::KEY_A))
		a -= _cam->GetRight() *t;
	if (Input::IsKeyPressed(Input::KEY_D))
		a += _cam->GetRight() *t;
	if (Input::IsKeyPressed(Input::KEY_Q))
		a -= _cam->GetUp() *t;
	if (Input::IsKeyPressed(Input::KEY_E))
		a += _cam->GetUp() *t;
	if (auxCheck2 == CAMERA_TYPE::FC)
		_cam->Move(a * _time->_deltaTime);

	if (Input::IsKeyDown(Input::KEY_X))
		_cam->DebugInfo();
	if (Input::IsKeyDown(Input::KEY_C))
		Input::toggle_lock_cursor();
	if (Input::IsKeyDown(Input::KEY_B))
		_cam->UpdateCameraType();
	if (Input::IsKeyDown(Input::KEY_SPACE))
		_cam->ToogleEjes();
<<<<<<< Updated upstream
=======

	if (Input::IsKeyDown(Input::KEY_UP))
		for (std::list<JuliEngine::Entity2*>::iterator it2 = JuliEngine::Entity2::EntitysLists.begin(); it2 != JuliEngine::Entity2::EntitysLists.end(); ++it2)
			if (*it2 == _a && it2 != JuliEngine::Entity2::EntitysLists.end())
			{
				it2--;
				_a = *it2;
			}
	if (Input::IsKeyDown(Input::KEY_DOWN))
		for (std::list<JuliEngine::Entity2*>::iterator it2 = JuliEngine::Entity2::EntitysLists.begin(); it2 != JuliEngine::Entity2::EntitysLists.end(); ++it2)
			if (*it2 == _a && it2 != JuliEngine::Entity2::EntitysLists.begin())
			{
				it2--;
				_a = *it2;
			}
	glm::vec3 b(0);

	if (_b!= nullptr)
	{
		if (Input::IsKeyDown(Input::KEY_0))
			b += _b->GetRight();
		if (Input::IsKeyDown(Input::KEY_1))
			b -= _b->GetRight();
		_b->Move(b * _time->_deltaTime * speed);
		if (Input::IsKeyDown(Input::KEY_2))
			_b->DebugInfo();
	}
>>>>>>> Stashed changes
}

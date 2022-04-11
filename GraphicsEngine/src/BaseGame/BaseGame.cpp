#include "BaseGame.h"

BaseGame::BaseGame() {

}
BaseGame::~BaseGame() {
	if (_window != nullptr) {
		_window = nullptr;
		delete _window;
	}
	if (_renderer != nullptr) {
		_renderer = nullptr;
		delete _renderer;
	}
}

int BaseGame::StartEngine(int width, int height, const char* windowName)
{
	if (InitEngine(width, height, windowName))
	{
		Init();
		while (!glfwWindowShouldClose(_window->GetWindow())) {
			_renderer->ClearScreen();
			_time->Update();

			Update();
			Draw();

			_renderer->PostRender(GetWindow());
		}
	}
	Deinit();
	DeinitEngine();
	return 0;
}
void BaseGame::DeinitEngine()
{
	glfwTerminate();
}
Window* BaseGame::GetWindow() {
	return _window;
}
bool BaseGame::InitEngine(int windowSizeX, int windowSizeY, std::string windowName)
{
	std::cout << "Initing Engine" << std::endl;
	if (!glfwInit())
		return false;

	_window = new Window(windowSizeX, windowSizeY, windowName);
	if (!_window->GetWindow())
	{
		glfwTerminate();
		delete _window;
		return false;
	}
	_window->Start();

	if (glewInit() != GLEW_OK) // tiene que ir despues de la creacion del contexto de glfw si o si
	{
		std::cout << "Glew error" << std::endl;
		return false;
	}

	_renderer = new Renderer();
	_renderer->Init();
	InitCamera();
	InitInput();
	_time = new Time();
	std::cout << "End Init Engine" << std::endl;
	return true;
}
Renderer* BaseGame::GetRenderer() {
	return _renderer;
}

double BaseGame::getCurrentTime()
{
	return glfwGetTime();
}
bool BaseGame::IsKeyDown(Input::KeyCode key) { return Input::IsKeyDown(key); }
bool BaseGame::IsKeyRelease(Input::KeyCode key) { return Input::IsKeyPressed(key); }
bool BaseGame::IsKeyUp(Input::KeyCode key) { return Input::IsKeyUp(key); }

void BaseGame::InitInput() {
	Input::SetWindow(_window);
	Input::StartInputSystem();
	Input::SetCam(_mainCamera);
}
void BaseGame::InitCamera() {
	_mainCamera = new Camera();
	_mainCamera->Init(_renderer,_window);
}
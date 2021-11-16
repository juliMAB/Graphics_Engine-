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
//bool BaseGame::InitEngine(int windowSizeX, int windowSizeY, std::string windowName)
//{
//	if (!glfwInit()) {
//		std::cout << "GLFW Initialization failed" << std::endl;
//		glfwTerminate();
//		return false;
//	}
//
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//
//	_window = new Window(windowSizeX, windowSizeY, windowName);
//	_renderer->Awake(_window);
//	int bufferWidth;
//	int bufferHeight;
//	glfwGetFramebufferSize(_window->GetWindow(), &bufferWidth, &bufferHeight);
//
//	_window->Start();
//	Input::SetWindow(_window);
//	Input::StartInputSystem();
//
//	if (!GlewStart()) {
//		glfwTerminate();
//		return false;
//	}
//	//enable or disable server - side GL capabilities
//	glEnable(GL_DEPTH);
//
//	_renderer = new Renderer();
//
//	_input = new Input();
//
//	_time = new Time();
//
//	return true;
//}
int BaseGame::StartEngine(int width, int height, const char* windowName)
{
	if (InitEngine(width, height, windowName))
	{
		Init();
		while (!glfwWindowShouldClose(_window->GetWindow())) {
			_time->Update();
			Update();
			Input::CheckClearInputList();
			glfwPollEvents();
			Draw();
			_renderer->SwapBuffers();
		}
	}
	Deinit();
	DeinitEngine();
	return 0;
}
bool BaseGame::GlewStart()
{
	_window->Start();
	if (glewInit())
		return false;
	_renderer->Start();
	return true;
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

	_renderer = new Renderer(_window);

	Input::SetWindow(_window);

	_time = new Time();

	return true;
}
Renderer* BaseGame::GetRenderer() {
	return _renderer;
}
void BaseGame::ClearWindow(float r, float g, float b, float a) { _window->ClearWindow(r, g, b, a); }
double BaseGame::getCurrentTime()
{
	return glfwGetTime();
}
bool BaseGame::IsKeyDown(Input::KeyCode key) { return Input::IsKeyDown(key); }
bool BaseGame::IsKeyRelease(Input::KeyCode key) { return Input::IsKeyRelease(key); }
bool BaseGame::IsKeyUp(Input::KeyCode key) { return Input::IsKeyUp(key); }
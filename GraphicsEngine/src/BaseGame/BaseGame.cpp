#include "BaseGame.h"

BaseGame::BaseGame() {
	_window = new Window();
	_renderer = new Renderer();
	_time = new Time();
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
	if (!glfwInit()) {
		std::cout << "GLFW Initialization failed" << std::endl;
		glfwTerminate();
		return 0;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	_window = new Window(width, height, windowName);
	_renderer->Awake(_window);
	int bufferWidth;
	int bufferHeight;
	glfwGetFramebufferSize(_window->GetWindow(), &bufferWidth, &bufferHeight);

	_window->Start();
	Input::SetWindow(_window);
	Input::StartInputSystem();

	if (!GlewStart()) {
		glfwTerminate();
		return 0;
	}
	//enable or disable server - side GL capabilities
	glEnable(GL_DEPTH);
	UpdateEngine();
}
void BaseGame::UpdateEngine()
{
	init();
	while (!glfwWindowShouldClose(_window->GetWindow())) {
		_time->Update();
		Update();	
		Input::CheckClearInputList();
		glfwPollEvents();
		Draw();
		_renderer->SwapBuffers();
	}
	Exit();
	Deinit();
}
void BaseGame::Draw() {
	
}
bool BaseGame::GlewStart()
{
	_window->Start();
	if (glewInit())
		return false;
	_renderer->Start();
	return true;
}
void BaseGame::Deinit()
{
	glfwTerminate();
}
void BaseGame::Exit() {
	_window->Exit();
}
Window* BaseGame::GetWindow() {
	return _window;
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
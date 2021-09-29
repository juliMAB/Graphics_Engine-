#include "BaseGame.h"

BaseGame::BaseGame() {
	_window = new Window();
	_renderer = new Renderer();
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
void BaseGame::Awake() {
	if (!glfwInit())
		Exit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	_window->Awake();
	_renderer->Awake(_window);
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

	_window->MakeWindow(width, height, windowName);
	//_window->Start();

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

}
void BaseGame::UpdateEngine()
{
	while (!glfwWindowShouldClose(_window->GetWindow())) {
		Update();	
		Input::CheckClearInputList();
		glfwPollEvents();
	}
}
void BaseGame::Start() {
	_window->Start();
	if (glewInit())
		int a = 1;
	_renderer->Start();
}
bool BaseGame::GlewStart()
{
	_window->Start();
	if (glewInit())
		return false;
	_renderer->Start();
	return true;
}
void BaseGame::End()
{
	_renderer->Exit();
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
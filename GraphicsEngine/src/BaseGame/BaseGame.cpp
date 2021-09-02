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
void BaseGame::Start() {
	_window->Start();
	
	if (glewInit())
		int a = 1;
	_renderer->Start();
}
void BaseGame::Update() {
	while (!glfwWindowShouldClose(_window->GetWindow())) {
		_window->Update();
		_renderer->Update();
		_window->PoolEvents();
		_window->SwapBuffers();
	}
}
void BaseGame::Exit() {
	_window->Exit();
}
Window* BaseGame::GetWindow() {
	return _window;
}
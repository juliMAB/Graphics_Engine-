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
void BaseGame::RunGame() {
	Awake();
	Start();
	Update();
	Exit();
}
void BaseGame::Awake() {
	if (!glfwInit())
		return;
	_window->Awake();
}
void BaseGame::Start() {
	_window->Start();
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
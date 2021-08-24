#include "BaseGame.h"
#include <iostream>
#include <time.h>
#include <glew.h>
#include <glfw/glfw3.h>
#include "../Window/Window.h"
#include "../Exports/Exports.h"

GameBase::GameBase() {
	srand(time(0));
	_window = new Window();
	_renderer = new Renderer();
}
GameBase::~GameBase() {
	if (_window != NULL) {
		delete _window;
		delete _renderer;
	}
}
int GameBase::StartEngine() {
	if (!glfwInit()) {
		std::cout << "GLFW Initialization failed" << std::endl;
		glfwTerminate();
		return 0;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	_window->MakeWindow(1365, 768, "SauronAndFeloz->Stefano(true);", NULL);
	_renderer->Init(_window);
	
	int bufferWidth;
	int bufferHeight;
	glfwGetFramebufferSize(_window->GetWindow(), &bufferWidth, &bufferHeight);

	_window->InitWindow();
}
void GameBase::UpdateEngine() {
	while (_window->CheckIfWindowIsOpen()) {
		Update();
		glfwPollEvents();
	}
}
void GameBase::EndEngine() {
	glfwTerminate();
}
Window* GameBase::GetWindow() {
	return _window;
}
Renderer* GameBase::GetRenderer() {
	return _renderer;
}
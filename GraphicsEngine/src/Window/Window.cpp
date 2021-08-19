#include "Window.h"
#include <iostream>

#include "glew.h"
#include "GLFW/glfw3.h"


	Window::Window() {
		_window=NULL;
	}
	Window::~Window() {

	}

	int Window::MakeWindow(int width, int height, const char* windowName, GLFWmonitor* fullScreen) {
		_window = glfwCreateWindow(width, height, windowName, fullScreen, NULL);

		if (!_window) {
			std::cout << "Fail to create GLFW window" << std::endl;
			return 0;
		}
		return 1;
	}

	void Window::InitWindow() {
		glfwMakeContextCurrent(_window);
	}

	void Window::ClearWindow(float r, float g, float b, float a) {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(r, g, b, a);
	}

	int Window::CheckIfWindowIsOpen() {
		return (!glfwWindowShouldClose(_window));
	}
	void Window::SwapBuffers() {
		glfwSwapBuffers(_window);
	}
	void Window::DestroyWindow() {
		glfwDestroyWindow(_window);
	}
	GLFWwindow* Window::GetWindow() {
		return _window;
	}

#include "Window.h"

Window::Window() {
	_window = nullptr;
}
void Window::Awake() {
	_window = glfwCreateWindow(640, 480, "SauronAndFeloz->Stefano(true)", NULL, NULL);
}
void Window::Start() {
	if (!_window) {
		Exit();
		return;
	}
	glfwMakeContextCurrent(_window);
}
void Window::Update() {
}
void Window::Exit() {
	glfwTerminate();
}
void Window::PoolEvents() {
	glfwPollEvents();
}
void Window::SwapBuffers(){
	glfwSwapBuffers(_window);
}
GLFWwindow* Window::GetWindow() {
	return _window;
}
void Window::ResizeWindow(int width, int height) {
	glfwSetWindowSize(_window, width, height);
}
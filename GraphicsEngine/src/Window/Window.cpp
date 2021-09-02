#include "Window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

Window::Window() {
	_window = nullptr;
}
void Window::Awake() {
	_window = glfwCreateWindow(640, 480, "SauronAndFeloz", NULL, NULL);
}
void Window::Start() {
	if (!_window) {
		Exit();
		return;
	}
	glfwMakeContextCurrent(_window);
	glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
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

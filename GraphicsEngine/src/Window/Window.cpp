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
int Window::MakeWindow(int w, int h, std::string name)
{
	_width = w;
	_height = h;
	_window = glfwCreateWindow(w, h, name.c_str(), NULL, NULL);
	if (!_window) {
		std::cout << "Fail to create GLFW window" << std::endl;
		return 0;
	}
	return 1;
}
GLFWwindow* Window::GetWindow() {
	return _window;
}
void Window::ResizeWindow(int width, int height) {
	glfwSetWindowSize(_window, width, height);
}
void Window::ClearWindow(float r, float g, float b, float a)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(r, g, b, a);
}
int Window::GetHeight()
{
	return _height;
}
int Window::GetWidth()
{
	return _width;
}

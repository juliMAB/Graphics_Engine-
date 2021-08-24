#include "Renderer.h"
#include "GLFW/glfw3.h"
#include <iostream>

Renderer::Renderer() {
	window = nullptr;
}
Renderer::~Renderer() {

}
void Renderer::Init(Window* window) {
	this->window = window;
}
void Renderer::SetClearWindow(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}
void Renderer::ClearWindow() {
	glClear(GL_COLOR_BUFFER_BIT);
}
void Renderer::SwapBuffers() {
	glfwSwapBuffers(window->GetWindow());
}
void Renderer::DrawTriangle(float size) {
	glBegin(GL_TRIANGLES);
	glVertex2f(-size, -size);
	glVertex2f(0.0f, size);
	glVertex2f(size, -size);
	glEnd();
	std::cout << "Triangulo Dibujado\n";	
}
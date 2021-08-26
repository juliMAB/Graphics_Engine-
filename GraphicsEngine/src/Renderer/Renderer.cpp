#include "Renderer.h"

Renderer::Renderer() {	
}
void Renderer::Awake(Window* window) {
	_window = window;
}
void Renderer::Start() {	
}
void Renderer::Update() {
	glClear(GL_COLOR_BUFFER_BIT);
	DrawTriangle(0.5f);
}
void Renderer::Exit() {

}
void Renderer::DrawTriangle(float size) {
	//glBegin(GL_TRIANGLES);
	//glVertex2f(-size, -size);
	//glVertex2f(0, size);
	//glVertex2f(size, -size);
	//glEnd();
	glBegin(GL_QUADS);
	glVertex2f(-size, -size);
	glVertex2f(-size, size);
	glVertex2f(size, -size);
	glVertex2f(size, size);
	glVertex2f(1, 1);
	glVertex2f(0.75, 1);
	glEnd();
}
void Renderer::SetClearWindow(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}
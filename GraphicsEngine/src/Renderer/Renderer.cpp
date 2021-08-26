#include "Renderer.h"

Renderer::Renderer() {
	_window = nullptr;
	buffer = 0;
}
void Renderer::Awake(Window* window) {
	_window = window;
}
void Renderer::Start() {
	float position[6] = {
		-0.5f, -0.5f,
		 0.0f,  0.5f,
		 0.5f, -0.5f
	};	
	
	//glGenBuffers(1, &buffer);
	//glBindBuffer(GL_ARRAY_BUFFER, buffer);
	//glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), position, GL_STATIC_DRAW);
}
void Renderer::Update() {
	glClear(GL_COLOR_BUFFER_BIT);
	DrawTriangle(0.5f);
}
void Renderer::Exit() {

}
void Renderer::BeginDrawing() {
	
}
void Renderer::DrawTriangle(float size) {
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	glBegin(GL_TRIANGLES);
	glVertex2f(-size, -size);
	glVertex2f(0, size);
	glVertex2f(size, -size);
	glEnd();
	//glBegin(GL_QUADS);
	//glVertex2f(-size, -size);
	//glVertex2f(-size, size);
	//glVertex2f(size, -size);
	//glVertex2f(size, size);
	//glVertex2f(1, 1);
	//glVertex2f(0.75, 1);
	//glEnd();
}
void Renderer::SetClearWindow(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}
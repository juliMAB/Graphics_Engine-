#ifndef RENDERER_H
#define RENDERER_H
#include "../Exports/Exports.h"
#include "../Window/Window.h"

class GraficosEngine_API Renderer {
private:
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
		"}\n\0";
	Window* _window;
	unsigned int buffer;
	unsigned int vertexShader, fragmentShader, programShader;
	unsigned int VBO, VAO, EBO;

public:
	Renderer();
	void Awake(Window* window);
	void Start();
	void Update();
	void Exit();
	void BeginDrawing();
	// --------------------
	void DrawTriangle(float size);
	void SetClearWindow(float r, float g, float b, float a);
	void ClearWindow();
	void ShadersStart();
	void ShadersUpdate();
	void SetVertexShader();
	void SetFragmentShader();
	void LinkShaders();
	void DrawTriangle();
	void SetTriangle();
	void SetQuad();
};
#endif
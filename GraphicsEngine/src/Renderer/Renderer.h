#ifndef RENDERER_H
#define RENDERER_H
#include "../Exports/Exports.h"
#include "../Window/Window.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class GraficosEngine_API Renderer {
private:
	const std::string standarPath = "../GraphicsEngine/Shaders";
	const std::string vertexPath = "../GraphicsEngine/Shaders/VertexShader.shader";
	const std::string fragmentPath = "../GraphicsEngine/Shaders/FragmentShader.shader";
		
	Window* _window;
	unsigned int buffer;
	unsigned int programShader;
	unsigned int VBO, VAO, EBO;

public:
	Renderer();
	void Awake(Window* window);
	void Start();
	void Load();
	void Update();
	void Exit();
	void BeginDrawing();
	// --------------------
	void DrawTriangle(float size);
	void SetClearWindow(float r, float g, float b, float a);
	void ClearWindow();
	void ShadersStart();
	void ShadersUpdate();
	void SetVertexShader(unsigned int &vertexShader, const char* vertexShaderSource);
	void SetFragmentShader(unsigned int &fragmentShader, const char* fragmentShaderSource);
	void LinkShaders(unsigned int vertexShader, unsigned int fragmentShader);
	void DrawTriangle();
	void SetTriangle();
	void SetQuad();
};
#endif
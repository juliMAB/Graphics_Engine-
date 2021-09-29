#ifndef RENDERER_H
#define RENDERER_H
#include "../Exports/Exports.h"
#include "../Window/Window.h"
#include "../GLM/mat4x4.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

static enum TypeShader {
	Colour,
	Texture
};
enum TypeShape {
	Triangle, Quad
};
typedef unsigned int uint;
class GraficosEngine_API Renderer {
private:
	const std::string vertexPath = "../GraphicsEngine/Shaders/VertexShader.shader";
	const std::string fragmentPath = "../GraphicsEngine/Shaders/FragmentShader.shader";

	Window* _window;
	//unsigned int buffer;
	unsigned int programShader;
	//unsigned int VBO, VAO, EBO;
public:
	Renderer();
	~Renderer();
	void Awake(Window* window);
	void Start();
	void Update();
	void Exit();
	void BeginDrawing();
	// --------------------
	//void DrawTriangle(float size);
	void SetClearWindow(float r, float g, float b, float a);
	void ClearWindow();
	void ShadersStart();
	std::string ReadVertexShader();
	std::string ReadFragmentShader();
	void ShadersUpdate();
	void SetVertexShader(unsigned int &vertexShader, const char* vertexShaderSource);
	void SetFragmentShader(unsigned int &fragmentShader, const char* fragmentShaderSource);
	void LinkShaders(unsigned int vertexShader, unsigned int fragmentShader);
	//void DrawTriangle();
	//void SetTriangle();
	void SetBuffers(int tam, float* verts, uint& vbo, uint& vao);
	void SetIndex(int tam, uint* indexs, uint& ibo);
	void Setattributes(uint location, int size, int stride, int offset);
	void Draw(TypeShape shape, int verts, uint vao, uint vbo, uint ibo, float* vertexs, float tamVertexs, TypeShader t);
	void UpdateMVP(glm::mat4 model, uint transformLoc);
	uint GetShader() { return programShader; };
};
#endif
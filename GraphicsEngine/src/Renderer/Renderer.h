#ifndef RENDERER_H
#define RENDERER_H
#include "../Exports/Exports.h"
#include "../Window/Window.h"
#include "../GLM/mat4x4.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


enum TypeShape {
	Triangle, Quad
};
static enum class TypeShader {
	Colour,
	Texture
};
typedef unsigned int uint;
class GraficosEngine_API Renderer {
private:

	const std::string vertexPath = "Shaders/VertexShader.shader";
	const std::string fragmentPath = "Shaders/FragmentShader.shader";

	Window* _window;
	uint programShader;
public:
	Renderer();
	~Renderer();
	void Awake(Window* window);
	void Start();
	void Update();
	// --------------------
	void SetClearWindow(float r, float g, float b, float a);
	void ClearWindow();
	void ShadersStart();
	std::string ReadVertexShader();
	std::string ReadFragmentShader();
	void SetVertexShader(unsigned int &vertexShader, const char* vertexShaderSource);
	void SetFragmentShader(unsigned int &fragmentShader, const char* fragmentShaderSource);
	void LinkShaders(unsigned int vertexShader, unsigned int fragmentShader);
	void SetBuffers(int tam, float* verts, uint& vbo, uint& vao);
	void SetIndex(int tam, uint* indexs, uint& ibo);
	void Setattributes(uint location, int size, int stride, int offset);
	void Draw(TypeShape shape, int verts, uint vao, uint vbo, uint ibo, float* vertexs, float tamVertexs);
	void Draw(TypeShape shape, int verts, uint vao, uint vbo, uint ibo, float* vertexs, float tamVertexs, TypeShader t);
	uint GetShader();
	void SwapBuffers();
	void UpdateMVP(glm::mat4 model, uint transformLoc, uint uniformView, uint uniformProjection, uint uniformColor, uint uniformAlpha, glm::vec4 color);

};
#endif
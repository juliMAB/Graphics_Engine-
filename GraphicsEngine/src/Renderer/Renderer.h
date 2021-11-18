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
	Triangle=3, Quad
};
static enum class TypeShader {
	Colour,
	Texture
};
typedef unsigned int uint;
static class GraficosEngine_API Renderer {
private:

	const std::string vertexPath = "Shaders/VertexShader.shader";
	const std::string fragmentPath = "Shaders/FragmentShader.shader";

	Window* _window;
	unsigned int programShader;
	void Start();
	//-------Shaders Staff----------
	std::string ReadVertexShader();
	std::string ReadFragmentShader();
	void SetVertexShader(unsigned int &vertexShader, const char* vertexShaderSource);
	void SetFragmentShader(unsigned int &fragmentShader, const char* fragmentShaderSource);
	void LinkShaders(unsigned int vertexShader, unsigned int fragmentShader);
	void ShadersStart();
	//--------------------------------
public:
	//----- C y D -------
	Renderer(Window* window);
	~Renderer();
	//----- C y D -------
	// --------------------
	void CreateNewBuffers(uint& VAO, uint& VBO, uint& EBO);
	void SetBuffers(int tam, float* verts, uint& vbo, uint& vao);
	void BindBuffer(uint VAO, uint VBO, uint EBO, float* vertices, uint sizeOfVertices, uint* indices, uint sizeOfIndices);
	void SetIndex(int tam, uint* indexs, uint& ibo);
	void Setattributes(uint location, int size, int stride, int offset);
	void Draw(uint vertices, uint _vao);
	void Draw(TypeShape shape, int verts, uint vao, uint vbo, uint ibo, float* vertexs, float tamVertexs);
	void Draw(TypeShape shape, int verts, uint vao, uint vbo, uint ibo, float* vertexs, float tamVertexs, TypeShader t);
	uint GetShader();
	void SwapBuffers();
	void UpdateMVP(glm::mat4 model, uint _uniformPos, uint uniformView, uint uniformProjection, uint uniformColor, uint uniformAlpha, glm::vec4 color);
	void DeleteBuffers(uint _vao, uint _vbo, uint _ebo);
	void DeleteExtraBuffer(int size, uint buffer);
};
#endif
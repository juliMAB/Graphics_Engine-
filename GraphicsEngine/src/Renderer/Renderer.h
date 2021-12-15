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

	const std::string vertexPathT = "Shaders/TextureVertexShader.shader";
	const std::string fragmentPathT = "Shaders/TextureFragmentShader.shader";
	const std::string vertexPathS = "Shaders/SolidVertexShader.shader";
	const std::string fragmentPathS = "Shaders/SolidFragmentShader.shader";

	Window* _window;
	uint programShaderT;
	uint programShaderS;
	void Start();
	//-------Shaders Staff----------
	std::string ReadVertexShader(std::string vPath);
	std::string ReadFragmentShader(std::string fPath);
	void SetVertexShader(unsigned int &vertexShader, const char* vertexShaderSource);
	void SetFragmentShader(unsigned int &fragmentShader, const char* fragmentShaderSource);
	void LinkShaders(unsigned int vertexShader, unsigned int fragmentShader, uint& programShader);
	void ShadersStart();
	//--------------------------------
public:
	//----- C y D -------
	Renderer(Window* window);
	~Renderer();
	// --------------------
	//void setCurrentTexture(Texture tex);
	void CreateNewBuffers(uint& VAO, uint& VBO, uint& EBO);
	void SetBuffers(int tam, float* verts, uint& vbo, uint& vao);
	void BindBuffer(uint VAO, uint VBO, uint EBO, float* vertices, uint sizeOfVertices, uint* indices, uint sizeOfIndices);
	void BindBuffer2(uint& VAO, uint& VBO, int tam, float* vertices);
	void BindBaseBufferRequest(uint VAO, uint VBO, uint EBO, float* vertices, uint sizeOfVertices, uint* indices, uint sizeOfIndices);
	void BindIndexes(uint& EBO, int tam, uint* indexs);
	void SetIndex(int tam, uint* indexs, uint& ibo);
	void Setattributes(uint location, int size, int stride, int offset);
	void CreateExtraBuffer(unsigned int& buffer, int size);
	void Draw(uint vertices, uint _vao);
	void Draw(int verts, uint vao, uint vbo, uint ibo, float* vertexs, float tamVertexs, uint shader);
	void Draw2(int verts, uint vao, uint vbo, uint ibo, float* vertexs, float tamVertexs, uint shader);
	void DrawM(glm::mat4 model, unsigned int VAO, unsigned int VBO, unsigned int& EBO, unsigned int vertices, unsigned int tamVerts, float* vertexs, unsigned int shaderId);
	void DrawM2(unsigned int VAO, unsigned int VBO, unsigned int& EBO, float* vertexs, uint tamVertsBit, uint* indices, uint tamIndicesBit, int cantVertices, unsigned int shaderId);
	void DrawM2(unsigned int VAO, int cantIndexes, unsigned int shaderId);
	void DrawM2Debug(unsigned int VAO, int cantIndexes, unsigned int shaderId);
	void DrawM2(unsigned int VAO, unsigned int VBO, unsigned int& EBO, unsigned int vertices, unsigned int tamVerts, float* vertexs, unsigned int shaderId);
	void DrawShape(glm::mat4 modelMatrix, unsigned int VAO, unsigned int vertices, unsigned int usedShaderID);
	void UpdateMVP(glm::mat4 model, uint transformLoc, uint uniformView, uint uniformProjection, uint shader);
	void UpdateMVP(glm::mat4 model, uint _uniformPos, uint uniformView, uint uniformProjection, uint uniformColor, uint uniformAlpha, glm::vec4 color, uint shader);
	void UpdateMVP(glm::mat4 model, uint _uniformPos, uint uniformView, uint uniformProjection, uint uniformColor, uint uniformAlpha, glm::vec4 color, uint uniformTex, uint textureID, uint shader);
	void SwapBuffers();
	void DeleteBuffers(uint _vao, uint _vbo, uint _ebo);
	void DeleteExtraBuffer(int size, uint buffer);
	void BindExtraBuffer(unsigned int buffer, float* data, unsigned int sizeOfData, unsigned int bufferType);
	uint GetShaderT();
	uint GetShaderS();
};
#endif
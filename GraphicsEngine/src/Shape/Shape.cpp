#include "Shape.h"
#include <iostream>
#include "../GLEW/glew.h"
#include "glfw3.h"
#include "../GLM/gtc/type_ptr.hpp"

uint posIndexs[] = {
	0, 1, 3,
	1, 2, 3
};

TypeShape typeOfShape;
uint tamVerts;
Shape::Shape(Renderer* rend, TypeShape typeShape)
{
	switch (typeShape) {
	case Triangle:
		tamVerts = 4 * 24;
		shapeVertices = new float [tamVerts] {
			 0.0f,  0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.5f,
			 0.5f, -0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 0.0f,
			 0.5f, -0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 1.0f
		};
		break;
	case Quad:
		tamVerts = 4 * 32;
		shapeVertices = new float [tamVerts] {
			// positions             colors                 texture coords
			 0.5f,  0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 1.0f, // top right
			 0.5f, -0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 1.0f  // top left 
		};
		break;
	default:
		break;
	}
	InitShape(typeShape);
	_usingTexture = false;
}
Shape::~Shape() {
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);
}
void Shape::DrawShape() 
{
	_renderer->UpdateMVP(model, transformLoc, _uniformView, _uniformProjection, _uniformColor, _uniformAlpha, color);
	if (_usingTexture) {
		_texture->UseTexture();
		_renderer->Draw(typeOfShape, sizeof(posIndexs) / sizeof(float), _vao, _vbo, _ebo, shapeVertices, tamVerts, TypeShader::Texture);
		_texture->StopTexture();
	}
	else
		_renderer->Draw(typeOfShape, sizeof(posIndexs) / sizeof(float), _vao, _vbo, _ebo, shapeVertices, tamVerts);
}
int Shape::GetVerticesArrLenght() {
	return tamVerts / sizeof(float);
}
int Shape::GetVerticesTam() {
	return tamVerts;
}
float* Shape::GetVertices() {
	return shapeVertices;
}
float Shape::GetVertexIndex(int ind) {
	return shapeVertices[ind];
}
void Shape::InitShape(TypeShape type) {
	typeOfShape = type;
	glUseProgram(_renderer->GetShader());
	_uniformColor = glGetUniformLocation(_renderer->GetShader(), "color");
	_uniformProjection = glGetUniformLocation(_renderer->GetShader(), "projection");
	_uniformView = glGetUniformLocation(_renderer->GetShader(), "view");
	_uniformAlpha = glGetUniformLocation(_renderer->GetShader(), "alpha");
	_texLocation = glGetAttribLocation(_renderer->GetShader(), "tex");
	glUseProgram(_renderer->GetShader());

	_renderer->SetBuffers(GetVerticesTam(), shapeVertices, _vbo, _vao);
	_renderer->SetIndex(GetVerticesTam(), posIndexs, _ebo);
	_renderer->Setattributes(_posLocation, 2, 8, 0);
	_renderer->Setattributes(_posColor   , 4, 8, 2);
	_renderer->Setattributes(_postexture , 2, 8, 6);

	// Default Attributes:
	SetPos(0, 0);
	SetRotations(0, 0, 0);
	SetScale(3);
	SetColor(1, 1, 1, 1);
}
void Shape::SetColor(float r, float g, float b)
{
	color = glm::vec4(r, g, b, 1.0f);
}
void Shape::SetColor(float r, float g, float b, float a)
{
	color = glm::vec4(r, g, b, a);
}
void Shape::SetColor(glm::vec3 color, float alpha)
{
	color = glm::vec4(color, alpha);
}
void Shape::SetColor(glm::vec4 color)
{
	color = glm::vec4(color);
}
void Shape::LoadTexture(const char* path, const char* name) {
	_texture = new Texture(path, name);
	if (!_texture->LoadTexture()) {
		std::cout << "Cant load texture in shape" << std::endl;
		delete _texture;
		_texture = NULL;
		_usingTexture = false;
		return;
	}
	std::cout << "Texture loaded in shape" << std::endl;
	_usingTexture = true;
}
#include "Shape.h"
#include <iostream>
#include "../GLEW/glew.h"
#include "glfw3.h"
#include "../GLM/gtc/type_ptr.hpp"

//uint posIndexs[] = {
//	0, 1, 3,
//	1, 2, 3
//};

TypeShape typeOfShape;
uint tamVerts;
int cantIndices;
const uint tam1Vert=8;
uint* indices;
uint indicesTam;
float* shapeVertices;
Shape::Shape(Renderer* rend, TypeShape typeShape)
{
	
	_renderer = rend;
	tamVerts = typeShape * tam1Vert;
	indicesTam = Triangle * (typeShape - 2);
	switch (typeShape) {
	case Triangle:
		shapeVertices = new float [tamVerts] {
			 0.0f,  0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.5f,
			 0.5f, -0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 0.0f,
			 0.5f, -0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 1.0f
		};
		indices =  new uint[indicesTam] {0, 1, 2};
		break;
	case Quad:
		shapeVertices = new float [tamVerts] {
			// positions             colors                 texture coords
			 0.5f,  0.5f, /**/ 0.0f, 0.0f, 0.0f, 0.0f, /**/ 1.0f, 1.0f, // top right
			 0.5f, -0.5f, /**/ 0.0f, 0.0f, 0.0f, 0.0f, /**/ 1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, /**/ 0.0f, 0.0f, 0.0f, 0.0f, /**/ 0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, /**/ 0.0f, 0.0f, 0.0f, 0.0f, /**/ 0.0f, 1.0f  // top left 
		};
		indices = new uint[indicesTam]{ 0, 1, 2, 2, 3, 0 };
		break;
	default:
		shapeVertices = new float [tamVerts];
		break;
	}
	_renderer->CreateNewBuffers(_vao, _vbo, _ebo);
	_renderer->BindBuffer(_vao, _vbo, _ebo, shapeVertices, sizeof(shapeVertices) * tamVerts, indices, sizeof(indices) * indicesTam);
	
	glUseProgram(_renderer->GetShader());
	_uniformPos        = glGetUniformLocation(_renderer->GetShader(), "transform");
	_uniformColor      = glGetUniformLocation(_renderer->GetShader(), "color");
	_uniformProjection = glGetUniformLocation(_renderer->GetShader(), "projection");
	_uniformView       = glGetUniformLocation(_renderer->GetShader(), "view");
	_uniformAlpha      = glGetUniformLocation(_renderer->GetShader(), "alpha");
	_texLocation       = glGetAttribLocation (_renderer->GetShader(), "tex");
	uint _useTexture   = glGetUniformLocation(_renderer->GetShader(), "useTexture");
	glUniform1i(_useTexture, false);
	glUseProgram(_renderer->GetShader());
	
	_renderer->Setattributes(_posLocation, 2, tam1Vert, 0);
	_renderer->Setattributes(_posColor   , 4, tam1Vert, 2);
	_renderer->Setattributes(_postexture , 2, tam1Vert, 6);

	delete[] indices;
	delete[] shapeVertices;
}
Shape::~Shape() {
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_ebo);
}
void Shape::Draw() 
{
	_renderer->UpdateMVP(model, _uniformPos, _uniformView, _uniformProjection, _uniformColor, _uniformAlpha, color);
		_renderer->Draw(indicesTam,_vao);
}
//void Shape::InitShape(TypeShape type) {
//	typeOfShape = type;
//	glUseProgram(_renderer->GetShader());
//	_uniformColor = glGetUniformLocation(_renderer->GetShader(), "acolor");
//	_uniformProjection = glGetUniformLocation(_renderer->GetShader(), "projection");
//	_uniformView = glGetUniformLocation(_renderer->GetShader(), "view");
//	_uniformAlpha = glGetUniformLocation(_renderer->GetShader(), "alpha");
//	_texLocation = glGetAttribLocation(_renderer->GetShader(), "tex");
//	glUseProgram(_renderer->GetShader());
//
//	//_renderer->SetBuffers(GetVerticesTam(), shapeVertices, _vbo, _vao);
//	//_renderer->SetIndex(GetVerticesTam(), posIndexs, _ebo);
//	_renderer->Setattributes(_posLocation, 2, 8, 0);
//	_renderer->Setattributes(_posColor   , 4, 8, 2);
//	_renderer->Setattributes(_postexture , 2, 8, 6);
//
//	// Default Attributes:
//	SetPos(0, 0);
//	SetRotations(0, 0, 0);
//	SetScale(3);
//}

//void Shape::LoadTexture(const char* path, const char* name) {
//	_texture = new Texture(path, name);
//	if (!_texture->LoadTexture()) {
//		std::cout << "Cant load texture in shape" << std::endl;
//		delete _texture;
//		_texture = NULL;
//		_usingTexture = false;
//		return;
//	}
//	std::cout << "Texture loaded in shape" << std::endl;
//	_usingTexture = true;
//}

//void Shape::SetShader()
//{
//	glm::vec3 newColor = glm::vec3(color.r, color.g, color.b);
//	uint colorLoc = glGetUniformLocation(_renderer->GetShader(), "aColor");
//	glUniform3fv(colorLoc, 1, glm::value_ptr(newColor));
//
//	uint alphaLoc = glGetUniformLocation(_renderer->GetShader(), "alpha");
//	glUniform1fv(alphaLoc, 1, &(color.a));
//}

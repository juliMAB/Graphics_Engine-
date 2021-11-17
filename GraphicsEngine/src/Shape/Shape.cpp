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
			 0.5f,  0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 1.0f, // top right
			 0.5f, -0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 1.0f  // top left 
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
	_uniformPos        = glGetUniformLocation(_renderer->GetShader(), "transform" );
	_uniformColor      = glGetUniformLocation(_renderer->GetShader(), "color"	  );
	_uniformProjection = glGetUniformLocation(_renderer->GetShader(), "projection");
	_uniformView       = glGetUniformLocation(_renderer->GetShader(), "view"	  );
	_uniformAlpha      = glGetUniformLocation(_renderer->GetShader(), "alpha"	  );
	_texLocation       = glGetAttribLocation (_renderer->GetShader(), "tex"		  );
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

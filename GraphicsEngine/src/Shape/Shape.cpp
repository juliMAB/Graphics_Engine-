#include "Shape.h"
#include <iostream>
#include "../GLEW/glew.h"
#include "glfw3.h"
#include "../GLM/gtc/type_ptr.hpp"



	static float triangleVerticesCol[18] = {
		0.0f, 0.5f, 0.0f,	/**/ 1.0f, 1.0f, 1.0f,/* 0.0f, 0.0f,*/
		0.5f, -0.5f, 0.0f,	/**/ 1.0f, 1.0f, 1.0f,/* 0.0f, 0.0f,*/
		-0.5f, -0.5f, 0.0f,	/**/ 1.0f, 1.0f, 1.0f,/* 0.0f, 0.0f */
	};

	static float quadVerticesCol[32] = {
		-1.0, 1.0, 1.0f, /**/ 1.0f, 0.0f, 0.0f,
		-1.0, -1.0, 1.0f, /**/ 0.0f, 1.0f, 0.0f,
		1.0, -1.0, 1.0f, /**/ 0.0f, 0.0f, 1.0f,
		1.0, 1.0, 1.0f, /**/ 0.0f, 0.0f, 0.0f,
	};

	unsigned int posIndexs[] = {
		0, 1, 2,
		2, 3, 0
	};

	typedef unsigned int uint;

	TypeShape typeOfShape;
	uint tamVerts;

	Shape::Shape(Renderer* rend) : Entity(rend) 
	{
	}
	Shape::~Shape() {
		glDeleteVertexArrays(1, &_vao);
		glDeleteBuffers(1, &_vbo);
	}

	void Shape::DrawShape() 
	{
		GetRenderer()->UpdateMVP(matrix.model, transformLoc, _uniformView, _uniformProjection,_uniformColor,_uniformAlpha,matrix.color);
		_renderer->Draw(typeOfShape, sizeof(posIndexs) / sizeof(float), _vao, _vbo, _ibo, _vb, tamVerts);
	}

	int Shape::GetVerticesArrLenght() {
		return tamVerts / sizeof(float);
	}
	int Shape::GetVerticesTam() {
		return tamVerts;
	}
	float* Shape::GetVertices() {
		return _vb;
	}
	float Shape::GetVertexIndex(int ind) {
		return _vb[ind];
	}
	void Shape::InitShape(TypeShape type) {
		typeOfShape = type;
		glUseProgram(_renderer->GetShader());
		_uniformColor = glGetUniformLocation(_renderer->GetShader(), "color");
		_uniformProjection = glGetUniformLocation(_renderer->GetShader(), "projection");
		_uniformView = glGetUniformLocation(_renderer->GetShader(), "view");
		_uniformAlpha = glGetUniformLocation(_renderer->GetShader(), "alpha");
		glUseProgram(_renderer->GetShader());
		switch (type) {
		case TypeShape::Triangle:
			_vb = triangleVerticesCol;
			tamVerts = sizeof(triangleVerticesCol);
			break;
		case TypeShape::Quad:
			_vb = quadVerticesCol;
			tamVerts = sizeof(quadVerticesCol);
			break;
		}
		_renderer->SetBuffers(GetVerticesTam(), _vb, _vbo, _vao);

		_renderer->Setattributes(_positionLocation, 3, 6, 0);
		_renderer->Setattributes(1, 3, 6, 3);
	}
	void Shape::SetColor(float r, float g, float b)
	{
		matrix.color = glm::vec4(r, g, b, 1.0f);
	}
	void Shape::SetColor(float r, float g, float b, float a)
	{
		matrix.color = glm::vec4(r, g, b, a);
	}
	void Shape::SetColor(glm::vec3 color, float alpha)
	{
		matrix.color = glm::vec4(color, alpha);
	}
	void Shape::SetColor(glm::vec4 color)
	{
		matrix.color = glm::vec4(color);
	}
	

#include "Shape.h"
#include <iostream>
#include "../GLEW/glew.h"
#include "glfw3.h"
#include "../GLM/gtc/type_ptr.hpp"



	static float triangleVerticesCol[18] = {
		0.0f, 0.5f, 0.0f,	/**/ 1.0f, 0.0f, 0.0f,/* 0.0f, 0.0f,*/
		0.5f, -0.5f, 0.0f,	/**/ 0.0f, 1.0f, 0.0f,/* 0.0f, 0.0f,*/
		-0.5f, -0.5f, 0.0f,	/**/ 0.0f, 0.0f, 1.0f,/* 0.0f, 0.0f */
	};

	static float quadVerticesCol[32] = {
		-1.0, 1.0, 1.0f, /**/ 1.0f, 0.0f, 0.0f,
		-1.0, -1.0, 1.0f, /**/ 0.0f, 1.0f, 0.0f,
		1.0, -1.0, 1.0f, /**/ 0.0f, 0.0f, 1.0f,
		1.0, 1.0, 1.0f, /**/ 0.0f, 0.0f, 0.0f,
	};

	

	//uint indexsPyramid[] = {
	//	0, 3, 1,
	//	1, 3, 2,
	//	2, 3, 0,
	//	0, 1, 2
	//};

	//uint indexsCube[] = {
	//	0, 1, 2,
	//	2, 3, 0,
	//	//3, 2, 0,
	//	//2, 1, 0,
	//	1, 5, 6,
	//	6, 2, 1,
	//	7, 6, 5,
	//	5, 4, 7,
	//	4, 0, 3,
	//	3, 7, 4,
	//	4, 5, 1,
	//	1, 0, 4,
	//	3, 2, 6,
	//	6, 7, 3
	//};

	unsigned int posIndexs[] = {
		0, 1, 2,
		2, 3, 0
	};

	typedef unsigned int uint;

	TypeShape typeOfShape;
	TypeShader typeShader;
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
		GetRenderer()->UpdateMVP(matrix.model, transformLoc, _uniformView, _uniformProjection);
		_renderer->Draw(typeOfShape, sizeof(posIndexs) / sizeof(float), _vao, _vbo, _ibo, _vb, tamVerts, TypeShader::Colour);
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
	void Shape::InitShape(TypeShape type, TypeShader t) {
		typeOfShape = type;
		typeShader = t;
		vertexColorLocation = glGetUniformLocation(GetRenderer()->GetShader(), "ourColor");
		_uniformProjection = glGetUniformLocation(_renderer->GetShader(), "projection");
		_uniformView = glGetUniformLocation(_renderer->GetShader(), "view");
		glUseProgram(GetRenderer()->GetShader());
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
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
		//CalcAverageNormals(GetIndexs(), 36, _vb, 64, 8, 5);
		_renderer->SetBuffers(GetVerticesTam(), _vb, _vbo, _vao);

		_renderer->Setattributes(_positionLocation, 3, 6, 0);
		_renderer->Setattributes(1, 3, 6, 3);
	}
	

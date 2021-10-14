#include "Shape.h"
#include <iostream>
#include "../GLEW/glew.h"
#include "glfw3.h"
#include "../GLM/gtc/type_ptr.hpp"



	static float triangleVerticesCol[] = {
		 0.0f,  0.5f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.0f
	};

	static float quadVerticesCol[] = {
		 0.5f,  0.5f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.0f
	};

	unsigned int posIndexs[] = {
		0, 1, 2,
		2, 3, 0
	};

	typedef unsigned int uint;

	TypeShape typeOfShape;
	uint tamVerts;

	Shape::Shape(Renderer* rend, TypeShape typeShape) : Entity(rend)
	{
		InitShape(typeShape);
		_usingTexture = false;
	}
	Shape::~Shape() {
		glDeleteVertexArrays(1, &_vao);
		glDeleteBuffers(1, &_vbo);
	}

	void Shape::DrawShape() 
	{
		GetRenderer()->UpdateMVP(matrix.model, transformLoc, _uniformView, _uniformProjection,_uniformColor,_uniformAlpha,matrix.color);
		if (_usingTexture) {
			_texture->UseTexture();
			GetRenderer()->Draw(typeOfShape, sizeof(posIndexs) / sizeof(float), _vao, _vbo, _ibo, _vb, tamVerts, TypeShader::Texture);
			_texture->StopTexture();
		}
		else
			GetRenderer()->Draw(typeOfShape, sizeof(posIndexs) / sizeof(float), _vao, _vbo, _ibo, _vb, tamVerts);
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
		_texLocation = glGetAttribLocation(_renderer->GetShader(), "tex");
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
		_renderer->SetIndex(GetVerticesTam(), posIndexs, _ibo);
		_renderer->Setattributes(_positionLocation, 3, 9, 0);
		_renderer->Setattributes(1, 4, 9, 3);
		_renderer->Setattributes(2, 2, 9, 7);

		// Default Attributes:
		SetPos(0, 0, 0);
		SetRotations(0, 0, 0);
		SetScale(3);
		SetColor(1, 1, 1, 1);
	}
	unsigned int* Shape::GetIndexs() {
		switch (typeOfShape) {
		default:
			return posIndexs;
			break;
		}
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
	

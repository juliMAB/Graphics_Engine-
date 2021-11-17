#ifndef ENTITY_H
#define ENTITY_H
#include "../Exports/Exports.h"
#include "../Renderer/Renderer.h"
#include <../GLM/glm.hpp>
#include <../GLM/gtc/matrix_transform.hpp>
#include <../GLM/gtc/type_ptr.hpp>
typedef unsigned int uint;
class GraficosEngine_API Entity {

protected:
	Renderer* _renderer;
	// mat4 para armar la model.
	glm::mat4 translate;
	glm::mat4 rotationX;
	glm::mat4 rotationY;
	glm::mat4 rotationZ;
	glm::mat4 scaleMat4;
	//----model-------
	glm::mat4 model;
	//--PosRotScale---
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;
	//----Color-------
	glm::vec4 color;
	//----------------
	void UpdateMatrixData();
	
	const static uint _posLocation = 0;
	const static uint _posColor = 1;
	const static uint _postexture= 2;
	uint _uniformPos;
	uint _uniformView;
	uint _uniformProjection;
	uint _uniformColor;
	uint _uniformAlpha;
	uint _texLocation;

	uint _vao, _vbo, _ebo, _vertices;
	
public:
	//---C y D----------
	Entity();
	~Entity();
	//------------------
	//----SetPos--------
	void SetPos(float x, float y);
	void SetPos(glm::vec2 pos);
	void SetPos(float x, float y, float z);
	void SetPos(glm::vec3 pos);
	//------------------
	//----SetRot--------
	void SetRotations(float x, float y, float z);
	void SetRotations(glm::vec3 rotation);
	void SetRotX(float x);
	void SetRotY(float y);
	void SetRotZ(float z);
	//------------------
	//----SetScale------
	void SetScale(glm::vec3 scale4);
	void SetScale(float x, float y, float z);
	void SetScale(float scale4);
	//----SetColor------
	void SetColor(glm::vec4 color);
	void SetColor(float r, float g, float b, float a);

	//----Getters-------
	glm::vec4 getColor();
	glm::vec3 getPos();
	glm::vec3 getRot();
	glm::vec3 getScale();
};

#endif
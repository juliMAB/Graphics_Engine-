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
	glm::mat4 scaleMat;
	//----model-------
	glm::mat4 model;
	//--PosRotScale---
	glm::vec3 v3pos;
	glm::vec3 v3rot;
	glm::vec3 v3scale;
	//----Color-------
	glm::vec4 color;
	//----------------
	void UpdateMatrixData();
	
	const static uint _posLocation = 0;
	const static uint _posColor = 1;
	const static uint _postexture= 2;
	uint transformLoc;
	uint _uniformView;
	uint _uniformProjection;
	uint _uniformColor;
	uint _uniformAlpha;
	uint _texLocation;
	
public:
	//--PosRotScale---
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	//---C y D----------
	Entity(Renderer* rend);
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
	void SetScale(glm::vec3 scale);
	void SetScale(float x, float y, float z);
	void SetScale(float scale);
};

#endif
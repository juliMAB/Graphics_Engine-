#ifndef ENTITY_H
#define ENTITY_H
#include "../Exports/Exports.h"
#include "../Renderer/Renderer.h"
#include <../GLM/glm.hpp>
#include <../GLM/gtc/matrix_transform.hpp>
#include <../GLM/gtc/type_ptr.hpp>

class GraficosEngine_API Entity {
private:
	glm::mat4 translate;
	glm::mat4 rotationX;
	glm::mat4 rotationY;
	glm::mat4 rotationZ;
	glm::quat rotationQuaternion;
	glm::mat4 scaleMat;
protected:
	Renderer* _renderer;
	glm::mat4 model;
	glm::vec4 color;
	
	void UpdateMatrixData();
	void UpdateTransformsData();
	typedef unsigned int uint;
	const static uint _posLocation = 0;
	const static uint _posColor = 1;
	const static uint _postexture= 2;
	uint transformLoc;
	uint _uniformView;
	uint _uniformProjection;
	uint _uniformColor;
	uint _uniformAlpha;
	uint _texLocation;
	
	Renderer* GetRenderer();
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	void SetRenderer(Renderer* r);
	
	Entity(Renderer* rend);
	~Entity();
	
	virtual void SetPos(float x, float y);
	virtual void SetPos(glm::vec2 pos);
	virtual void SetRotX(float x);
	virtual void SetRotY(float y);
	virtual void SetRotZ(float z);

	virtual void SetRotations(float x, float y, float z);
	virtual void SetRotations(glm::vec3 rotation);

	virtual void SetScale(float x, float y, float z);
	void SetScale(float scale);
};

#endif
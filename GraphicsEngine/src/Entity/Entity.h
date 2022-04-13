#ifndef ENTITY_H
#define ENTITY_H
#include "../Exports/Exports.h"
#include "../Renderer/Renderer.h"
#include <../GLM/glm.hpp>
#include <../GLM/gtc/matrix_transform.hpp>
#include <../GLM/gtc/type_ptr.hpp>
#include "../Juli/Jinterface.h"
struct Transform
{
	glm::vec3 position;
	glm::vec3 lastPosition;
	glm::vec3 eulerAngles;
	glm::vec3 scale;
	glm::quat rotation;

	glm::vec3 localPosition;
	glm::vec3 localEulerAngles;
	glm::vec3 localScale;
	glm::quat localRotation;

	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 right;
};

struct Matrix
{
	glm::mat4 model;
	glm::mat4 translate;
	glm::mat4 rotationX;
	glm::mat4 rotationY;
	glm::mat4 rotationZ;
	glm::mat4 scale;
};


class GraficosEngine_API Entity {

	
public:
	//---C y D----------
	Entity();
	Entity(Renderer* renderer);
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
	void SetScale(float x, float y);
	void SetScale(float x, float y, float z);
	void SetScale(float scale4);
	//----SetColor------

	//----Getters-------
	glm::vec3 getPos();
	glm::vec3 getRot();
	glm::vec3 getScale();
	glm::vec3 getLastPos();
	void Draw(uint shaderId);


private:
	glm::vec3 QuatToVec(glm::quat quat, glm::vec3 vec);
protected:
	Renderer* _renderer;

	Transform transform;
	Matrix matrix;

	uint _uniformModel;
	uint _uniformView;
	uint _uniformProjection;
	uint _locationPosition;
	uint _locationNormal;
	uint _locationTexCoord;

	virtual void SetUniforms();
	//uint _vao, _vbo, _ebo, tam, indicesTam;
	color::RGBA _color;
	//----Updates-------

	void UpdateMatrixData();
	void UpdateTransform();
};

#endif
#ifndef ENTITY_H
#define ENTITY_H
#include "../Exports/Exports.h"
#include "../Renderer/Renderer.h"
#include <../GLM/glm.hpp>
#include <../GLM/gtc/matrix_transform.hpp>
#include <../GLM/gtc/type_ptr.hpp>

struct Triangle {
	glm::vec2 point1;
	glm::vec2 point2;
	glm::vec2 point3;
};

class GraficosEngine_API Entity {
private:
	struct Transform {
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
		glm::quat rotationQuaternion;

		glm::vec3 localPosition;
		glm::vec3 localRotation;
		glm::vec3 localScale;

		glm::vec3 forward;
		glm::vec3 up;
		glm::vec3 right;
	};
	struct Matrix {
		glm::mat4 model;
		glm::mat4 translate;
		glm::mat4 rotationX;
		glm::mat4 rotationY;
		glm::mat4 rotationZ;
		glm::mat4 scale;
	};
protected:
	glm::vec3 _worldUp;
	Renderer* _renderer;
	void UpdateMatrixData();
	void UpdateTransformsData();
	typedef unsigned int uint;
	const static uint _positionLocation = 0;
	const static uint _positionColor = 1;
	uint transformLoc;
	uint _uniformView;
	uint _uniformProjection;
	
	Renderer* GetRenderer();
public:
	void SetRenderer(Renderer* r);
	//void DrawTriangle(Triangle triangle, Color color);
	//void SetTriangle();
	//------------------------------------
	Entity(Renderer* rend);
	~Entity();

	Transform transform;
	Matrix matrix;
	
	virtual void SetPos(float x, float y, float z);
	virtual void SetPos(glm::vec3 pos);
	virtual void SetRotX(float x);
	virtual void SetRotY(float y);
	virtual void SetRotZ(float z);

	virtual void SetRotations(float x, float y, float z);
	virtual void SetRotations(glm::vec3 rotation);

	virtual void SetScale(float x, float y, float z);
};

#endif
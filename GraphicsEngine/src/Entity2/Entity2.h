#ifndef ENTITY2_H
#define ENTITY2_H
#include "Exports/Exports.h"
#include "Renderer/Renderer.h"
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"
#include "Juli/Jinterface.h"
#include <iostream>
#include <list>
#include "Behaviour/Behaviour.h"
namespace JuliEngine
{
	class GraficosEngine_API Entity2 : public Behaviour {
	public:
		static int CuantityEntitys;
		static std::list<Entity2*> EntitysLists;
		////---C y D----------
		//Entity2();
		//Entity2(Renderer* renderer);
		//~Entity2();
		////------------------
		////----SetPos--------
		//void SetPos(float x, float y);
		//void SetPos(glm::vec2 pos);
		//void SetPos(float x, float y, float z);
		//void SetPos(glm::vec3 pos);
		////------------------
		////----SetRot--------
		//void SetRotations(float x, float y, float z);
		//void SetRotations(glm::vec3 rotation);
		//void SetRotX(float x);
		//void SetRotY(float y);
		//void SetRotZ(float z);
		////------------------
		////----SetScale------
		//void SetScale(glm::vec3 scale4);
		//void SetScale(float x, float y);
		//void SetScale(float x, float y, float z);
		//void SetScale(float scale4);
		////----SetColor------
		//void SetColor(float x, float y, float z, float w);
		//void SetColor(float x, float y, float z);
		////----Getters-------
		//glm::vec3 getPos();
		//glm::vec3 getRot();
		//glm::vec3 getScale();
		//glm::vec3 getLastPos();
		//glm::vec3 getColor();
		//void Draw(uint shaderId);

		////---other---
		//void DebugInfo();


	private:
		friend class MyImGui;
	protected:
		Renderer* _renderer;

		Transform transform;

		uint _locationPosition;
		uint _locationNormal;
		uint _locationTexCoord;

		//virtual void SetUniforms();
		//
		//void UpdateMatrixData();
		//void UpdateTransform();
	};
}


#endif
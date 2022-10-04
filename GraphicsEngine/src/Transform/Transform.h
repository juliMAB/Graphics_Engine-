#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "GLM/glm.hpp"
#include "GLM/gtc/type_ptr.hpp"
#include "Exports/Exports.h"
#include "Component/Component.h"
using namespace glm;
using namespace std;
#define MAXCHILDREN 500;
namespace JuliEngine
{
	class GraficosEngine_API Transform :public Component
	{
	public:
		Transform();
		Transform(GameObject* gameObject);
		Transform(GameObject* gameObject, Entity2* ourEntity);
		~Transform();
		//---GETTERS---
		glm::vec3 getpos();
		glm::vec3 getrot();
		glm::vec3 getscl();

		glm::vec3 getPos(glm::mat4 mat);
		glm::vec3 getRot(glm::mat4 mat);
		glm::vec3 getScl(glm::mat4 mat);

		glm::vec3 getForward();
		glm::vec3 getRight();
		glm::vec3 getUp();

		glm::mat4 getModel();

		glm::mat4 getLocalModel();
		

		//---SETERS---

		void setPos(glm::vec3 pos);
		void setRot(glm::vec3 rot);
		void setScl(glm::vec3 scl);

		void setMatrix(glm::mat4 mat);
		void setParentModel(glm::mat4 mat);
		
	private:
		void setRotRadians(glm::vec3 rot);

		void setRotX(float x);
		void setRotY(float y);
		void setRotZ(float z);

		glm::vec3 localpos;
		glm::vec3 localRot;
		glm::vec3 localScl;

		glm::vec3 globalpos;
		glm::vec3 globalRot;
		glm::vec3 globalSca;

		glm::vec3 localForward;
		glm::vec3 localRight;
		glm::vec3 localUp;

		glm::mat4 worldModel;
		glm::mat4 localModel;
		glm::mat4 parentModel;

		glm::mat4 localTranslate;
		glm::mat4 localRotateX;
		glm::mat4 localRotateY;
		glm::mat4 localRotateZ;
		glm::mat4 localScale;

		bool useLocalMatrix;

		void updateTransformRotation();

		void updateModelMatrix();
		
		glm::quat getRotationByMatrix(glm::mat4 mat);
		glm::vec3 QuatToVec(quat quat, vec3 vec);
		glm::quat EulerToQuat(vec3 euler);
		glm::vec3 toEulerRad(glm::quat rot);
		glm::vec3 normalizeAngles(glm::vec3 angles);
		float normalizeAngle(float angle);
	};

}
#endif // !TRANSFORM_H

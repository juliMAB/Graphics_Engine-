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

<<<<<<< Updated upstream
		vec3 getposition()			        { return m_pos			; };
		vec3 geteulerAngles()		        { return m_eulerRot		; };
		vec3 getlocalScale()		        { return m_scale		; };
		
		mat4 getWorldModel()				{ return worldModel     ; };
		mat4 getLocalModel()				{ return localModel     ; };
		mat4 getParentModel()				{ return parentModel    ; };

		glm::vec3 getRight()	;
		glm::vec3 getUp()		;
		glm::vec3 getBackward() ;
		glm::vec3 getForward()  ;
		
		void setposition   (vec3 v) { m_pos      = v; };
		void seteulerAngles(vec3 v) { m_eulerRot = v; updateTransformRotation(); };
		void setlocalScale (vec3 v) { m_scale    = v;};
=======
		//---Seters---
		void setPos		  (vec3 v);
		void setRot		  (vec3 v);
		void setRotRadians(vec3 v);
		void setScale	  (vec3 v);

		void setRotX(float x);
		void setRotY(float y);
		void setRotZ(float z);

		void setWorldModelWithParentModel(glm::mat4 localModel);
		void setMatrix(glm::mat4 mat);

		

		//---Getters---
		vec3 getPos();
		vec3 getRot();
		vec3 getScale();
>>>>>>> Stashed changes

		vec3 getPos(glm::mat4 mat);
		vec3 getRot(glm::mat4 mat);
		vec3 getScale(glm::mat4 mat);

		quat getRotationByMatrix(glm::mat4 mat);

		vec3 getRight();
		vec3 getUp();
		vec3 getBackward();
		vec3 getForward();

		mat4 getModel();
		mat4 getLocalModel();

<<<<<<< Updated upstream
		void updateLocalModelMatrix();
=======
		void updateModelMatrix();

		void UseLocalMatrix();

		
>>>>>>> Stashed changes
	protected:
		glm::vec3 globalPos;
		glm::vec3 globalRot;
		glm::vec3 globalScale;

		glm::vec3 localPos;
		glm::vec3 localRot;
		glm::vec3 localScale;

		glm::mat4 worldModel;
		glm::mat4 localModel;
		glm::mat4 parentModel;

		glm::mat4 modelMatrix;

		glm::mat4 matlocalTranslate;
		glm::mat4 matlocalRotateX;
		glm::mat4 matlocalRotateY;
		glm::mat4 matlocalRotateZ;
		glm::mat4 matlocalScale;

		bool useLocalMatrix;
	private:


		void updateTransformRotation();

		
		
	};
#pragma region OTHERS
	vec3 static QuatToVec(quat quat, vec3 vec);
	quat static EulerToQuat(vec3 euler);
	vec3 static toEulerRad(quat rot);
	vec3 static normalizeAngles(vec3 angles);
	float static normalizeAngle(float angle);
#pragma endregion

}
#endif // !TRANSFORM_H

#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "Component/Component.h"
#include "GLM/glm.hpp"
//#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"
using namespace glm;
namespace JuliEngine
{
	class Transform : Component
	{
	public:
		Transform();
		~Transform();
#pragma region GETTERS
		vec3 getposition()			{ return position		; };
		vec3 getlocalPosition()		{ return localPosition	; };
		vec3 geteulerAngles()		{ return eulerAngles	; };
		vec3 getright()				{ return right			; };
		vec3 getup()				{ return up				; };
		vec3 getforward()			{ return forward		; };
		quat getrotation()			{ return rotation		; };
		quat getlocalRotation()		{ return localRotation	; };
		vec3 getlocalScale()		{ return localScale		; };
		vec3 getlossyScale()		{ return lossyScale		; };
		Transform* getparent()		{ return parent			; };

#pragma endregion

#pragma region SETTERS
		void setposition(vec3 v) { position = v; setWMatrixTranslate(); };
		void setlocalPosition(vec3 v) { localPosition = v; };
		void seteulerAngles(vec3 v) { eulerAngles = v; };
		void setright(vec3 v) { right = v; };
		void setup(vec3 v) { up = v; };
		void setforward(vec3 v) { forward = v; };
		void setrotation(vec3 v) { rotation = v; };
		void setlocalRotation(vec3 v) { localRotation = v; };
		void setlocalScale(vec3 v) { localScale = v; };
		void setlossyScale(vec3 v) { lossyScale = v; };
		void setparent(Transform* v) { parent = v; };

#pragma endregion

	private:
		vec3 position;
		vec3 localPosition;
		vec3 eulerAngles;
		vec3 right;
		vec3 up;
		vec3 forward;
		quat rotation;
		quat localRotation;
		vec3 localScale;
		vec3 lossyScale;
		Transform* parent;
		mat4x4 worldToLocalMatrix;
		mat4x4 localToWorldMatrix;
		mat4 baseMatrix;
		mat4 translate;
		mat4 rotationX;
		mat4 rotationY;
		mat4 rotationZ;
		mat4 scale;
		list<Transform> childs;


		void setWMatrixTranslate() { translate = glm::translate(mat4(1.0f), position);  }
		void updateTransformRotation();
		void updateMatrix() { baseMatrix = translate * rotationX * rotationY * rotationZ * scale; }
	};
#pragma region OTHERS
	vec3 static QuatToVec(quat quat, vec3 vec);
	quat static EulerToQuat(vec3 euler);
#pragma endregion

}
#endif // !TRANSFORM_H

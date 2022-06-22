#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "GLM/glm.hpp"
#include "GLM/gtc/type_ptr.hpp"
#include "Exports/Exports.h"
#include "Component/Component.h"
//#include <list>
//#include <list>
using namespace glm;
using namespace std;
#define MAXCHILDREN 500;
namespace JuliEngine
{
	class GraficosEngine_API Transform :public Component
	{
	public:
		Transform(){};
		Transform(GameObject* gameObject);
		~Transform();
#pragma region GETTERS
		vec3 getposition()			{ return position		; };
		vec3 geteulerAngles()		{ return eulerAngles	; };
		vec3 getlocalScale()		{ return localScale		; };

		vec3 getright()				{ return right			; };
		vec3 getup()				{ return up				; };
		vec3 getforward()			{ return forward		; };
		
		Transform* getparent()		{ return parent			; };
		list<Transform*> getChilds(){ return childs			; };
		
		mat4 getmodel()				{return m_modelMatrix	; };
		Transform* getChilds(int v);
#pragma endregion

#pragma region SETTERS
		void setposition(vec3 v) { position = v; m_isDirty = true; updateSelfAndChild(); };
		void seteulerAngles(vec3 v) { eulerAngles = v; updateTransformRotation(); updateSelfAndChild();};
		void setlocalScale(vec3 v) { localScale = v; updateSelfAndChild();};

		void setright	(vec3 v) { right	= v; };
		void setforward	(vec3 v) { forward	= v; };
		void setup		(vec3 v) { up		= v; };

		void setparent(Transform* v) { parent = v; v->childs.push_back(this); };
		
		glm::mat4 getLocalModelMatrix();
#pragma endregion
		void updateSelfAndChild();
	protected:

	private:
		int const MAXCHILDRENS = 500;

		vec3 position;
		vec3 eulerAngles;
		vec3 right;
		vec3 up;
		vec3 forward;
		vec3 localScale;
		Transform* parent;
		bool m_isDirty;

		mat4 m_modelMatrix;
		list<Transform*> childs;

		void updateTransformRotation();
		void computeModelMatrix();
		void computeModelMatrix(const glm::mat4& parentGlobalModelMatrix);
		void forceUpdateSelfAndChild();
	};
#pragma region OTHERS
	vec3 static QuatToVec(quat quat, vec3 vec);
	quat static EulerToQuat(vec3 euler);
#pragma endregion

}
#endif // !TRANSFORM_H

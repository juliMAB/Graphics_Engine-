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
		Transform(GameObject* gameObject);
		Transform(GameObject* gameObject, Entity2* ourEntity);
		~Transform();
#pragma region GETTERS
		vec3 getposition()			{ return m_pos			; };
		vec3 geteulerAngles()		{ return m_eulerRot		; };
		vec3 getlocalScale()		{ return m_scale		; };


		
		Transform* getparent()		{ return parent			; };
		list<Transform*> getChilds(){ return childs			; };
		
		mat4 getmodel()				{return m_modelMatrix	; };
		Transform* getChilds(int v);
#pragma endregion

		void setposition(vec3 v) { m_pos = v; m_isDirty = true; updateSelfAndChild(); };
		void seteulerAngles(vec3 v) { m_eulerRot = v; updateTransformRotation(); updateSelfAndChild();};
		void setlocalScale(vec3 v) { m_scale = v; updateSelfAndChild();};

		void setForward	(vec3 v) { forward	= v; };
		void setRight	(vec3 v) { right	= v; };
		void setUp		(vec3 v) { up		= v; };

		void setparent(Transform* v) { parent = v; v->childs.push_back(this); };
		
		glm::mat4 getLocalModelMatrix();
		void updateSelfAndChild();

		glm::vec3 getRight()	;
		glm::vec3 getUp()		;
		glm::vec3 getBackward() ;
		glm::vec3 getForward()  ;

		glm::vec3 getGlobalScale();

		const glm::vec3& getGlobalPosition() const;
		const glm::vec3& getLocalPosition() const;
		const glm::vec3& getLocalRotation() const;
		const glm::vec3& getLocalScale() const;
		const glm::mat4& getModelMatrix() const;
	protected:
	private:
		int const MAXCHILDRENS = 500;

		vec3 m_pos;
		vec3 m_eulerRot;
		vec3 right;
		vec3 up;
		vec3 forward;
		vec3 m_scale;
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

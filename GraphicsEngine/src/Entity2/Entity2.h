#ifndef ENTITY2_H
#define ENTITY2_H
#include "Exports/Exports.h"
#include "Renderer/Renderer.h"
#include <iostream>
#include <list>
#include "GameObject/GameObject.h"
namespace JuliEngine
{
	class GraficosEngine_API Entity2 : public GameObject {
	public:
		static int CuantityEntitys;
		static std::list<Entity2*> EntitysLists;
		
		Entity2(Renderer* renderer);
		~Entity2();
		////------------------
		////----SetPos--------
		void SetPos(glm::vec3 pos);
		void SetPos(float x, float y, float z)	{SetPos(vec3(x	   , y    , z		  )); }
		void SetPos(float x, float y)			{SetPos(vec3(x	   , y    , getPos().z)); }
		void SetPos(glm::vec2 pos)				{SetPos(vec3(pos.x, pos.y, getPos().z)); }
		////------------------
		////----SetRot--------
		void SetRotations(glm::vec3 rotation)	 {if(getisStatic())return; getTransform()->seteulerAngles(rotation); }
		void SetRotX(float x)					 {vec3 a = getTransform()->geteulerAngles(); SetRotations(vec3(x, a.y, a.z)); }
		void SetRotY(float y)                    {vec3 a = getTransform()->geteulerAngles(); SetRotations(vec3(a.x, y, a.z)); }
		void SetRotZ(float z)                    {vec3 a = getTransform()->geteulerAngles(); SetRotations(vec3(a.x, a.y, z)); }
		void SetRotations(float x, float y, float z)								  { SetRotations(vec3(x, y, z));	 }
		////------------------
		////----SetScale------
		void SetScale(glm::vec3 v)				 { if (getisStatic())return; getTransform()->setlocalScale(v);		}
		void SetScale(float x, float y)			 { SetScale(vec3(x, y, getScale().z	)); }
		void SetScale(float x, float y, float z) { SetScale(vec3(x, y, z));				}
		void SetScaleAllSame(float v)			 { SetScale(v, v, v);					}
		void SetScaleMulty(float v)				 { vec3 a = getScale(); SetScale(a.x * v,a.y*v,a.z*v); }
		////----Getters-------
		glm::vec3 getPos()		{ return getTransform()->getposition   (); }
		glm::vec3 getRot()		{ return getTransform()->geteulerAngles(); }
		glm::vec3 getScale()	{ return getTransform()->getlocalScale (); }
		glm::vec3 GetUp()		{ return getTransform()->getup		   (); }
		glm::vec3 GetFront()	{ return getTransform()->getforward	   (); }
		glm::vec3 GetRight()	{ return getTransform()->getright	   (); }
		Renderer* getRender()	{ return _renderer; }
		Transform* getTransform() { return GameObject::getTransform(); }
		////---other---
		vec3 getColor() { return _color; };
		void SetColor(vec3 v) { _color = v; _renderer->UpdateColor(_uniformColor, _color); };
		void DebugInfo();

		void Update();

	private:
		friend class MyImGui;
	protected:
		vec3 _color;
		Renderer* _renderer;

		uint _locationPosition;
		uint _locationNormal;
		uint _locationTexCoord;
		uint _uniformColor;
		virtual void SetUniforms();
	};
}


#endif
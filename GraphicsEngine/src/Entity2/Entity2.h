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
		void SetPos(glm::vec3 pos)				{ transform.setposition(pos			   ); }
		void SetPos(float x, float y, float z)	{ SetPos(vec3(x	   , y    , z		  )); }
		void SetPos(float x, float y)			{ SetPos(vec3(x	   , y    , getPos().z)); }
		void SetPos(glm::vec2 pos)				{ SetPos(vec3(pos.x, pos.y, getPos().z)); }
		////------------------
		////----SetRot--------
		void SetRotations(glm::vec3 rotation)	 { transform.seteulerAngles(rotation); }
		void SetRotX(float x)					 { vec3 a = transform.geteulerAngles(); SetRotations(vec3(x, a.y, a.z)); }
		void SetRotY(float y)                    { vec3 a = transform.geteulerAngles(); SetRotations(vec3(a.x, y, a.z)); }
		void SetRotZ(float z)                    { vec3 a = transform.geteulerAngles(); SetRotations(vec3(a.x, a.y, z)); }
		void SetRotations(float x, float y, float z)								  { SetRotations(vec3(x, y, z));	 }
		////------------------
		////----SetScale------
		void SetScale(glm::vec3 v)				 { transform.setlocalScale(v);			}
		void SetScale(float x, float y)			 { SetScale(vec3(x, y, getScale().z	)); }
		void SetScale(float x, float y, float z) { SetScale(vec3(x, y, z));				}
		void SetScaleAllSame(float v)			 { SetScale(v, v, v);					}
		void SetScaleMulty(float v)				 { vec3 a = getScale(); SetScale(a.x * v,a.y*v,a.z*v); }
		////----Getters-------
		glm::vec3 getPos()		{ return transform.getposition	 (); }
		glm::vec3 getRot()		{ return transform.geteulerAngles(); }
		glm::vec3 getScale()	{ return transform.getlocalScale (); }
		////---other---
		void DebugInfo();


	private:
		//friend class MyImGui;
	protected:
		Renderer* _renderer;

		uint _locationPosition;
		uint _locationNormal;
		uint _locationTexCoord;

		virtual void SetUniforms();
	};
}


#endif
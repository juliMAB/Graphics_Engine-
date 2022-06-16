#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Object/Object.h"
#include "Transform/Transform.h"
namespace JuliEngine
{
	class GraficosEngine_API GameObject : protected Object
	{
	public:
		GameObject() { active = true; layer = 0; /*transform = Transform();*/ tag = ""; };
		~GameObject() { transform.~Transform(); };
		Transform getTransform() { return transform; };
		int getLayer() { return layer; };
		bool getactive() { return active; };
		string getTag() { return tag; };
		bool getisStatic() { return isStatic; };

		void setLayer(int v) { layer = v; };
		void setActive(bool v) { active = v; };
		void setTag(string v) { tag = v; };
		/// <summary>
		/// Tener en cuenta que mientras sea estatic no se puede mover.
		/// </summary>
		/// <param name="value"></param>
		void setisStatic(bool v) { isStatic = v; };

	protected:
	private:
		Transform transform;
		int layer;
		bool active;
		string tag;
		bool isStatic;

	};

}

#endif // !GAMEOBJECT_H

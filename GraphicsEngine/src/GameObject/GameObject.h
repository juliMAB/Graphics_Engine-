#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Object/Object.h"
#include "Transform/Transform.h"
namespace JuliEngine
{
	class GraficosEngine_API GameObject : protected Object
	{
	public:
		GameObject();
		~GameObject();
		int getLayer() { return layer; };
		bool getactive() { return active; };
		string getTag() { return tag; };
		bool getisStatic() { return isStatic; };
		string getName() { return _name; };

		void setLayer(int v) { layer = v; };
		void setActive(bool v) 
		{
			active = v;
			if (transform->getChilds().size() > 0)
				for (int i = 0; i < transform->getChilds().size(); i++)
				{
					transform->getChilds(i)->getGameObject()->setActive(v);
				}
		};
		void setTag(string v) { tag = v; };
		/// <summary>
		/// Tener en cuenta que mientras sea estatic no se puede mover.
		/// </summary>
		/// <param name="value"></param>
		void setisStatic(bool v) { isStatic = v; };
		void setName(string v) { _name = v; };

	protected:
		Transform* getTransform() { return transform; }
	private:
		Transform* transform;
		int layer;
		bool active;
		//bool isShoweable;
		string tag;
		bool isStatic;
		string _name;

	};

}

#endif // !GAMEOBJECT_H

#ifndef COMPONENT_H
#define COMPONENT_H
#include "Object/Object.h"
//#include "Transform/Transform.h"
namespace JuliEngine
{
class Transform;
class GameObject;
	class GraficosEngine_API Component : public Object
	{
    public:
        Component() { tag = "default"; AddDescription("-> ||Component|| ");};
        Component(Transform* transform, GameObject* gameObject);
		~Component();
        Transform* getTransform() { return transform; };
        GameObject* getGameObject() { return gameObject; };

    protected:
            
       
        void setTag(string v) { tag = v; };
        string getTag() { return tag; };
	private:
            //
            // Resumen:
            //     The tag of this game object.
        string tag;
        //
            // Resumen:
            //     The game object this component is attached to. A component is always attached
            //     to a game object.
        // public GameObject gameObject{ get; }

        Transform* transform;
        GameObject* gameObject;

	};
}
#endif // !COMPONENT_H

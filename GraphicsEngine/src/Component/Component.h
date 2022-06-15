#ifndef COMPONENT_H
#define COMPONENT_H
#include "Object/Object.h"
#include "Transform/Transform.h"
namespace JuliEngine
{
	class GraficosEngine_API Component : public Object
	{
    public:
		Component();
		~Component();

    protected:
            
       
        void setTag(string v) { tag = v; };
        string getTag() { return tag; };
        Transform getTransform() { return transform; };
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

        Transform transform;

	};
}
#endif // !COMPONENT_H

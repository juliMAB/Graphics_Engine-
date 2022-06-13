#ifndef COMPONENT_H
#define COMPONENT_H
#include "Object/Object.h"
namespace JuliEngine
{
	class Component : Object
	{
	public:
		Component();
		~Component();

       // public Transform transform{ get; }
            
       
        void SetTag(string tag);
        string GetTag();
	private:
            //
            // Resumen:
            //     The tag of this game object.
        string _tag;
        //
            // Resumen:
            //     The game object this component is attached to. A component is always attached
            //     to a game object.
        // public GameObject gameObject{ get; }


	};
}
#endif // !COMPONENT_H

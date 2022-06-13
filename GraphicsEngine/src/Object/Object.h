#ifndef OBJECT_H
#define OBJECT_H


#include "HideFlags.h"
#include <string>
#include <list>
using namespace std;
namespace JuliEngine
{
	class Object
	{
	public:
		Object();
		~Object();

		HideFlags GethideFlags();
		void SethideFlags(HideFlags hidenFlags);
		string Getname();
		void Setname(string name);


		static bool operator ==(Object x, Object y);
		static bool operator !=(Object x, Object y);
	private:
		//
		// Resumen:
		//     Should the object be hidden, saved with the Scene or modifiable by the user?
		HideFlags _hideFlags;
			//
			// Resumen:
			//     The name of the object.
		string _name;
		int m_instanceID;
		int static m_index;
		static list<Object*> lisObjects;
	};
}
#endif // !OBJECT_H
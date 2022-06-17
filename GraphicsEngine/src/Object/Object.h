#ifndef OBJECT_H
#define OBJECT_H

#include "Exports/Exports.h"
#include "HideFlags.h"
#include <string>
#include <list>
using namespace std;
namespace JuliEngine
{
	class GraficosEngine_API Object
	{
	public:

		Object();
		~Object();
		void AddDescription(string name);
	protected:

		string Getname();
		void Setname(string name);

		bool operator==(const Object& x) const;
		bool operator!=(const Object& x) const;
	private:
			//
			// Resumen:
			//     The name of the object.
		string _name;
		string _baseDescription;
		int m_instanceID;
		int static m_index;
		static list<Object*> lisObjects;
	};
}
#endif // !OBJECT_H
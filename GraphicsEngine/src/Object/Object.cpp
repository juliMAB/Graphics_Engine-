#include "Object.h"
namespace JuliEngine
{
#pragma region PRIVATE_VARIABLES
	int Object::m_index = 0;
	list<Object*> Object::lisObjects;
#pragma endregion
#pragma region CONSTRUCTORS
	Object::Object()
	{
		m_instanceID = m_index;
		m_index++;
		lisObjects.push_front(this);
	}
	Object::~Object()
	{
	}
#pragma endregion
#pragma region GETTERS


	HideFlags Object::GethideFlags()
	{
		return _hideFlags;
	}


	string Object::Getname()
	{
		return _name;
	}



#pragma endregion
#pragma region SETTERS
	void Object::Setname(string name)
	{
		_name = name;
	}
	void Object::SethideFlags(HideFlags hidenFlags)
	{
		_hideFlags = hidenFlags;
	}

#pragma endregion
#pragma region OPERATORS





	bool Object::operator==(const Object& x) const
	{
		return *this == x;
	}

	bool Object::operator!=(const Object& x) const
	{
		return *this != x;
	}
#pragma endregion

}
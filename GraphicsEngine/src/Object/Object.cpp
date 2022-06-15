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
		lisObjects.push_front(this);
		_name = "Object + " + m_index;
		m_index++;
	}
	Object::~Object()
	{
		lisObjects.remove(this);
	}
#pragma endregion
#pragma region GETTERS


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
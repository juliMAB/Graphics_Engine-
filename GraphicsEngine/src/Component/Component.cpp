#include "Component.h"
namespace JuliEngine
{
#pragma region PRIVATE_VARIABLES
#pragma endregion
#pragma region CONSTRUCTORS
Component::Component()
{
}

Component::~Component()
{
}


#pragma endregion
#pragma region GETTERS
string Component::GetTag()
{
	return string();
}
#pragma endregion
#pragma region SETTERS
void Component::SetTag(string tag)
{
	_tag = tag;
}
#pragma endregion
#pragma region OPERATORS
#pragma endregion
}


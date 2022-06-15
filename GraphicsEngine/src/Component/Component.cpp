#include "Component.h"
namespace JuliEngine
{
#pragma region PRIVATE_VARIABLES
#pragma endregion
#pragma region CONSTRUCTORS
#pragma endregion
#pragma region GETTERS
#pragma endregion
#pragma region SETTERS
#pragma endregion
#pragma region OPERATORS
#pragma endregion
	Component::Component():Object()
	{
		tag = "default";
		//transform = Transform();
	}
	Component::~Component()
	{
		//transform.~Transform();
	}
}


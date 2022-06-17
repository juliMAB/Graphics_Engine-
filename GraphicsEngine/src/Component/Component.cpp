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
	Component::Component(Transform* transform, GameObject* gameObject)
	{
		this->transform = transform;
		this->gameObject = gameObject;
		tag = "default";
		AddDescription("-> ||Component|| ");
	}
}


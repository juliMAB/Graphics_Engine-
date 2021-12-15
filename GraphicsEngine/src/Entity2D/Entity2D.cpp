#include "Entity2D.h"

glm::vec3 Entity2D::GetPivot()
{
    return getPos();
}

void Entity2D::InitCollider()
{
	colliderSize = 
	{
		getScale().x / 8.0f,
		getScale().y / 8.0f,
		getScale().z / 8.0f
	};
	pivot = 
	{
		getPos().x / getScale().x,
		getPos().y / getScale().y,
		getPos().z
	};
}

Entity2D::Entity2D()
{

}

Entity2D::~Entity2D()
{
}

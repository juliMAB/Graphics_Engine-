#include "Entity2D.h"

glm::vec3 Entity2D::GetPivot()
{
    return getPos();
}

void Entity2D::InitCollider()
{
	colliderSize = 
	{
		getScale().x,
		getScale().y,
		getScale().z
	};
	pivot = 
	{
		getPos().x,
		getPos().y,
		getPos().z
	};
}

Entity2D::Entity2D()
{

}

Entity2D::~Entity2D()
{
}

#ifndef ENTITY2D_H
#define ENTITY2D_H

#include "../Exports/Exports.h"
#include "../Entity/Entity.h"

class GraficosEngine_API Entity2D : public Entity {
public:

	bool _hasCollider, _moveable;
	glm::vec3 pivot;
	glm::vec3 colliderSize;
	glm::vec3 GetPivot();
	void InitCollider();
	Entity2D();
	~Entity2D();
};
	


#endif
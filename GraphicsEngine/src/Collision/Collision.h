#ifndef COLLISION_H
#define COLLISION_H

#include "../Exports/Exports.h"
#include "../Entity2D/Entity2D.h"

const float collisionMover = 0.00f;

class GraficosEngine_API Collision
{
public:
	Collision();
	~Collision();

	static void CollisionUpdate(Entity2D* entity1, Entity2D* entity2);
	static bool CheckCollisionRecRec(Entity2D* entity1, Entity2D* entity2);
	static bool CheckCollisionCircleCirclePivot(Entity2D* entity1, Entity2D* entity2);
	static void Overlap(Entity2D* entity1, Entity2D* entity2);

	static void GoLastPos(Entity2D* entity1, Entity2D* entity2);

private:

};

	


#endif // !COLLISION_H
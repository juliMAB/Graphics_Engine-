#include "collision.h"
#include <math.h>

	const float overlapSpeed = 0.25f;

	Collision::Collision()
	{

	}

	Collision::~Collision()
	{

	}

	void Collision::CollisionUpdate(Entity2D* entity1, Entity2D* entity2)
	{
		if (CheckCollisionRecRec(entity1, entity2))
		{
			std::cout << "Collision!" << std::endl;

			Overlap(entity1, entity2);
		}
	}

	bool Collision::CheckCollisionRecRec(Entity2D* entity1, Entity2D* entity2)
	{
		if (entity2->_hasCollider && entity1->_hasCollider)
		{
			bool collisionX = entity1->getPos().x - (entity1->getScale().x / 2) + entity1->getScale().x >= entity2->getPos().x - (entity2->getScale().x / 2)
				&& entity2->getPos().x - (entity2->getScale().x / 2) + entity2->getScale().x >= entity1->getPos().x - (entity1->getScale().x / 2);
			// collision y-axis?
			bool collisionY = entity1->getPos().y - (entity1->getScale().y / 2) + entity1->getScale().y >= entity2->getPos().y - (entity2->getScale().y / 2)
				&& entity2->getPos().y - (entity2->getScale().y / 2) + entity2->getScale().y >= entity1->getPos().y - (entity1->getScale().y / 2);
			// collision only if on both axes
			return collisionX && collisionY;
		}
		return false;
	}

	void Collision::Overlap(Entity2D* entity1, Entity2D* entity2) //Separa ambos objetos en el caso de existir overlap
	{
		if (entity2->_moveable)
		{
			glm::vec3 director = glm::vec3();
			director = entity1->GetPivot() - entity2->GetPivot(); //Genero el vector director para saber hacia donde puedo 

			do
			{
				director = glm::normalize(entity2->GetPivot() - entity1->GetPivot());
				entity2->SetPos(entity2->GetPivot() + director * overlapSpeed);
			} while (CheckCollisionRecRec(entity1, entity2));
		}
	}

	void Collision::GoLastPos(Entity2D* entity1, Entity2D* entity2)
	{
		if (entity2->_moveable)
			entity2->SetPos(entity2->getLastPos());
		if (entity1->_moveable)
			entity1->SetPos(entity1->getLastPos());
		
	}

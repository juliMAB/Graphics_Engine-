#ifndef ENTITY2D_H
#define ENTITY2D_H

#include "../Exports/Exports.h"
#include "../Entity/Entity.h"
#include "../Material/Material.h"

class GraficosEngine_API Entity2D : public Entity {
protected:
	glm::vec3 _bc2D;
public:
	Material* _mat;
	Entity2D(Renderer* rend, Material* mat);
	~Entity2D();
	void SetBoxCollider(float x, float y, float z);
	glm::vec3 GetBoxCollider();
	void SetMaterial(Material* mat);
	Material* GetMaterial();
};
	


#endif
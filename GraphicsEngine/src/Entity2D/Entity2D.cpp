#include "Entity2D.h"

Entity2D::Entity2D(Renderer* rend, Material* mat) : Entity(rend) {
	_bc2D.x = 1;
	_bc2D.y = 1;
	_bc2D.z = 1;
	_mat = mat;
}
Entity2D::~Entity2D() {
	if (_mat != NULL) {
		delete _mat;
		_mat = NULL;
	}
}
void Entity2D::SetBoxCollider(float x, float y, float z) {
	_bc2D.x = x;
	_bc2D.y = y;
	_bc2D.z = z;
}
glm::vec3 Entity2D::GetBoxCollider() {
	return _bc2D;
}
void Entity2D::SetMaterial(Material* mat) {
	_mat = mat;
}

Material* Entity2D::GetMaterial() {
	if (_mat != NULL)
		return _mat;
}
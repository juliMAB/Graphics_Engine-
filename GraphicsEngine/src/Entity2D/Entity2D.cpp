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

void Entity2D::UpdateShader()
{
	_renderer->UpdateMVP(matrix.model);
}
void Entity2D::AffectedLight(bool value)
{
	affectedLight = value;
}

void Entity2D::Draw()
{
	if (_material != nullptr)
	{
		_material->UpdateMaterial();
	}

	_renderer->Draw(_VAO, _VBO, _EBO, vertices, tam, vertexs);
}

Entity2D::Entity2D() : Entity()
{
	_color = color::RGBA();
	_material = nullptr;

	_VAO = 0;
	_VBO = 0;
	_EBO = 0;
	tam = 0;
	vertexs = 0;
	vertices = 0;

	_hasCollider = false;
	_moveable = false;

	useTexture = false;
	useMaterial = false;
	affectedLight = true;
}

Entity2D::Entity2D(Renderer* render) : Entity(render)
{
	_color = color::RGBA();
	_material = nullptr;

	_VAO = 0;
	_VBO = 0;
	_EBO = 0;
	tam = 0;
	vertexs = 0;
	vertices = 0;

	_hasCollider = false;
	_moveable = false;

	useTexture = false;
	useMaterial = false;
	affectedLight = true;
}

Entity2D::~Entity2D()
{
}
void Entity2D::UpdateMaterial()
{
	if (useMaterial)
	_material->UpdateMaterial();
}

void Entity2D::SetMateria(MaterialS* mat)
{
	useMaterial = true;
	_material = new Material(_renderer);
	_material->Init();
	_material->SetMaterial(mat);
	_material->UpdateMaterial();

}

void Entity2D::SetUniforms()
{
	Entity::SetUniforms();
	
	
}

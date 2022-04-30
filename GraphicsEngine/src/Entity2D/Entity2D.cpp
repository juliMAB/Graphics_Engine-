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
	_renderer->UpdateMVP(_uniformTransform, _uniformView, _uniformProjection, matrix.model);
	_renderer->UpdateColor(_uniformColor, _uniformAlpha, _color.GetColorV4());
	_renderer->UpdateBoolValue(_uniformAffectedLight, affectedLight);
	_renderer->UpdateBoolValue(_uniformUseTexture, useTexture);
	_renderer->UpdateBoolValue(_uniformUseMaterial, useMaterial);
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

	_uniformColor = 0;
	_uniformAlpha = 0;
	_uniformUseTexture = 0;
	_uniformUseMaterial = 0;
	_uniformAffectedLight = 0;

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

	_uniformColor = 0;
	_uniformAlpha = 0;
	_uniformUseTexture = 0;
	_uniformUseMaterial = 0;
	_uniformAffectedLight = 0;

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

void Entity2D::SetMateria(MaterialS mat)
{
	useMaterial = true;
	_material = new Material(_renderer);
	_material->SetMaterial(mat);
	_material->Init();
	_material->UpdateMaterial();

}

void Entity2D::SetUniforms()
{
	Entity::SetUniforms();
	_renderer->SetUniform(_uniformColor, "color");
	_renderer->SetUniform(_uniformAlpha, "alpha");
	_renderer->SetUniform(_uniformUseTexture, "useTexture");
	_renderer->SetUniform(_uniformAffectedLight, "affectedLight");
	_renderer->SetUniform(_uniformUseMaterial, "affectedMaterial");
	
}

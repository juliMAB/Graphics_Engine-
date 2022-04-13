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
	_renderer->UpdateMVP(_uniformModel, _uniformView, _uniformProjection, matrix.model);
	_renderer->UpdateColor(_uniformColor, _uniformAlpha, _color.GetColor());
	_renderer->UpdateBoolValue(_uniformAffectedLight, affectedLight);
	_renderer->UpdateBoolValue(_uniformUseTexture, useTexture);
	_renderer->UpdateBoolValue(_uniformUseMaterial, useMaterial);
}

void Entity2D::Draw()
{
	if (material != nullptr)
	{
		material->UpdateShader();
	}

	_renderer->Draw(_VAO, _VBO, _EBO, vertices, tam, vertexs);
}

Entity2D::Entity2D() : Entity()
{
	_color = color::RGBA();
	material = nullptr;

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
	material = nullptr;

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
	useMaterial = true;
	affectedLight = true;
}

Entity2D::~Entity2D()
{
}

void Entity2D::SetUniforms()
{
	Entity::SetUniforms();
	_renderer->SetUniform(_uniformColor, "color");
	_renderer->SetUniform(_uniformAlpha, "a");
	_renderer->SetUniform(_uniformUseTexture, "useTexture");
	_renderer->SetUniform(_uniformUseMaterial, "useMaterial");
	_renderer->SetUniform(_uniformAffectedLight, "affectedLight");
}

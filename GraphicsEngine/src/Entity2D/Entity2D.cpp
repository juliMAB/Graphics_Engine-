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
	_renderer->UpdateMVP(_uniformPos, _uniformView, _uniformProjection, model);
	_renderer->UpdateColor(_uniformColor, _uniformAlpha, color);
	_renderer->UpdateBoolValue(uniformAffectedLight, affectedLight);
	_renderer->UpdateBoolValue(uniformUseTexture, useTexture);
	_renderer->UpdateBoolValue(uniformUseMaterial, useMaterial);
}

Entity2D::Entity2D()
{

}

Entity2D::~Entity2D()
{
}

void Entity2D::SetUniforms()
{
	Entity::SetUniforms();
	renderer->SetUniform(uniformColor, "color");
	renderer->SetUniform(uniformAlpha, "a");
	renderer->SetUniform(uniformUseTexture, "useTexture");
	renderer->SetUniform(uniformUseMaterial, "useMaterial");
	renderer->SetUniform(uniformAffectedLight, "affectedLight");
}

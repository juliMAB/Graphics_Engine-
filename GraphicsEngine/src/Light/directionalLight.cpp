#include "DirectionalLight.h"

DirectionLight::DirectionLight(Renderer* render) : Light(render)
{
	direction = glm::vec3(0);
	_uniformDirection = 0;
}

void DirectionLight::SetUniforms()
{
	_renderer->SetUniform(_uniformDirection, "light.direction");
	Light::SetUniforms();
}

void DirectionLight::UpdateLight()
{
	_renderer->UseShader();
	_renderer->UpdateVec3(_uniformDirection, direction);
	_renderer->CleanShader();
	Light::UpdateLight();
}

DirectionLight::~DirectionLight()
{
	direction = glm::vec3(0);
	_uniformDirection = 0;
}

void DirectionLight::SetDirection(glm::vec3 direction)
{
	this->direction = direction;
}

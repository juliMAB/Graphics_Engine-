#include "DirectionalLight.h"

DirectionLight::DirectionLight(Renderer* render) : Light(render)
{
	direction = glm::vec3(0);
	_uniformDirection = 0;
}
DirectionLight::DirectionLight() : Light()
{
	direction = glm::vec3(0);
	_uniformDirection=0;

}

void DirectionLight::Init()
{
	_name = "dirLight";
	SetUniforms(_name);
}
void DirectionLight::SetUniforms(std::string name)
{
	_renderer->SetUniform(_uniformDirection, (name + ".direction").c_str());
	Light::SetUniforms(name);
}

void DirectionLight::UpdateLight()
{
	Light::UpdateLight();
	_renderer->UseShader();
	_renderer->UpdateVec3(_uniformDirection, direction);
	if (!_enabled)
		_renderer->UpdateVec3(_uniformDirection, vec3(0,0,0));
	_renderer->CleanShader();
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

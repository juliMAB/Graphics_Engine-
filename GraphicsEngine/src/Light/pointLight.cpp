#include "pointLight.h"
int PointLight::quantity =0;
PointLight::PointLight(Renderer* render) : Light(render)
{

	constant=0;
	linear=0;
	quadratic=0;

	_uniformPosition =0;
	_uniformConstant =0;
	_uniformLinear   =0;
	_uniformQuadratic=0;
	SetUniforms();
	_name = "pointLights[" + std::to_string(quantity) + " ] ";
	_name;
}

void PointLight::SetUniforms()
{
	_renderer->SetUniform(_uniformPosition, (_name + ".position").c_str());
	_renderer->SetUniform(_uniformConstant, (_name + ".constant").c_str());
	_renderer->SetUniform(_uniformLinear, (_name + ".linear").c_str());
	_renderer->SetUniform(_uniformQuadratic, (_name + ".quadratic").c_str());
	Light::SetUniforms(_name);
}

void PointLight::UpdateLight()
{
	pos = getPos();
	_renderer->UseShader();
	_renderer->UpdateVec3(_uniformPosition, pos);
	_renderer->UpdateFloatValue(_uniformConstant, constant);
	_renderer->UpdateFloatValue(_uniformLinear, linear);
	_renderer->UpdateFloatValue(_uniformQuadratic, quadratic);
	_renderer->CleanShader();
	Light::UpdateLight();
}

PointLight::~PointLight()
{
}


void PointLight::SetConstant(float constant)
{
	this->constant = constant;
}

void PointLight::SetLinear(float linear)
{
	this->linear = linear;
}

void PointLight::SetQuadratic(float quadratic)
{
	this->quadratic = quadratic;
}

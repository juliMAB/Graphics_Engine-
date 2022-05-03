#include "pointLight.h"

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
}

void PointLight::SetUniforms()
{
	_renderer->SetUniform(_uniformPosition, "light.position");
	_renderer->SetUniform(_uniformConstant, "light.constant");
	_renderer->SetUniform(_uniformLinear, "light.linear");
	_renderer->SetUniform(_uniformQuadratic, "light.quadratic");
	Light::SetUniforms();
}

void PointLight::UpdateLight()
{
	_renderer->UseShader();
	_renderer->UpdateVec3(_uniformPosition, getPos());
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

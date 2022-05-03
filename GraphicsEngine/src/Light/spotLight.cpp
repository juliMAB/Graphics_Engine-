#include "spotLight.h"

SpotLight::SpotLight(Renderer* render) : Light(render)
{
	SetUniforms();
}

void SpotLight::SetUniforms()
{
	_renderer->SetUniform(_uniformPosition, "light.position");
	_renderer->SetUniform(_uniformDirection, "light.direction");
	_renderer->SetUniform(_uniformCutOff, "light.cutOff");
	_renderer->SetUniform(_uniformConstant, "light.constant");
	_renderer->SetUniform(_uniformLinear, "light.linear");
	_renderer->SetUniform(_uniformQuadratic, "light.quadratic");
	Light::SetUniforms();
}

void SpotLight::UpdateLight()
{
	_renderer->UseShader();
	_renderer->UpdateVec3(_uniformPosition, cam->getPos());
	_renderer->UpdateVec3(_uniformDirection, cam->GetFront());
	_renderer->UpdateFloatValue(_uniformCutOff, cutOff);
	_renderer->UpdateFloatValue(_uniformConstant, constant);
	_renderer->UpdateFloatValue(_uniformLinear, linear);
	_renderer->UpdateFloatValue(_uniformQuadratic, quadratic);
	_renderer->CleanShader();
	Light::UpdateLight();
}

SpotLight::~SpotLight()
{
}

void SpotLight::SetCamera(Camera* cam)
{
	this->cam = cam;
}



void SpotLight::SetCutOff(float cutOff)
{
	this->cutOff = cutOff;
}

void SpotLight::SetConstant(float constant)
{
	this->constant = constant;
}

void SpotLight::SetLinear(float linear)
{
	this->linear = linear;
}

void SpotLight::SetQuadratic(float quadratic)
{
	this->quadratic = quadratic;
}


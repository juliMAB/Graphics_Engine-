#include "pointLight.h"
namespace JuliEngine
{

	int PointLight::quantity =0;
	PointLight::PointLight(Renderer* render) : Light(render)
	{

		constant = 0;
		linear = 0;
		quadratic = 0;

		_uniformPosition = 0;
		_uniformConstant = 0;
		_uniformLinear = 0;
		_uniformQuadratic = 0;
	}
	void PointLight::Init()
	{
		setName("pointLights[" + std::to_string(quantity) + "]");
		quantity++;
		SetUniforms(getName());
	}

	void PointLight::SetUniforms(std::string name)
	{
		Light::SetUniforms(name);
		_renderer->SetUniform(_uniformPosition, (name + ".position").c_str());
		_renderer->SetUniform(_uniformConstant, (name + ".constant").c_str());
		_renderer->SetUniform(_uniformLinear, (name + ".linear").c_str());
		_renderer->SetUniform(_uniformQuadratic, (name + ".quadratic").c_str());
	}

	void PointLight::UpdateLight()
	{
		Light::UpdateLight();
		pos = getPos();
		_renderer->UseShader();
		_renderer->UpdateVec3(_uniformPosition, pos);
		_renderer->UpdateFloatValue(_uniformConstant, constant);
		_renderer->UpdateFloatValue(_uniformLinear, linear);
		_renderer->UpdateFloatValue(_uniformQuadratic, quadratic);
		_renderer->CleanShader();
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
}

#include "pointLight.h"


	PointLight::PointLight(Renderer* render) : Light(render)
	{
		constant = 0.f;
		linear = 0.f;
		quadratic = 0.f;

		uniformConstant = 0;
		uniformLinear = 0;
		uniformQuadratic = 0;
	}

	PointLight::~PointLight()
	{
	}

	void PointLight::Init(int index)
	{
		std::string indexSTR = std::to_string(index).c_str();
		_renderer->SetUniform(uniformColor, ("pointLight[" + indexSTR + "].color").c_str());
		_renderer->SetUniform(uniformPosition, ("pointLight[" + indexSTR + "].position").c_str());
		_renderer->SetUniform(uniformAmbient, ("pointLight[" + indexSTR + "].ambient").c_str());
		_renderer->SetUniform(uniformDiffuse, ("pointLight[" + indexSTR + "].diffuse").c_str());
		_renderer->SetUniform(uniformSpecular, ("pointLight[" + indexSTR + "].specular").c_str());
		_renderer->SetUniform(uniformConstant, ("pointLight[" + indexSTR + "].constant").c_str());
		_renderer->SetUniform(uniformLinear, ("pointLight[" + indexSTR + "].linear").c_str());
		_renderer->SetUniform(uniformQuadratic, ("pointLight[" + indexSTR + "].quadratic").c_str());
		_renderer->SetUniform(uniformEnabled, ("pointLight[" + indexSTR + "].enabled").c_str());
	}

	void PointLight::UseLight()
	{
		_renderer->UseShader();
		_renderer->UpdateLight(uniformColor, color.GetColor());
		_renderer->UpdateLight(uniformPosition, transform.position);
		_renderer->UpdateLight(uniformAmbient, ambient);
		_renderer->UpdateLight(uniformDiffuse, diffuse);
		_renderer->UpdateLight(uniformSpecular, specular);
		_renderer->UpdateFloatValue(uniformConstant, constant);
		_renderer->UpdateFloatValue(uniformLinear, linear);
		_renderer->UpdateFloatValue(uniformQuadratic, quadratic);
		_renderer->UpdateBoolValue(uniformEnabled, enabled);
		_renderer->CleanShader();
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

	float PointLight::GetConstant()
	{
		return constant;
	}

	float PointLight::GetLinear()
	{
		return linear;
	}

	float PointLight::GetQuadratic()
	{
		return quadratic;
	}

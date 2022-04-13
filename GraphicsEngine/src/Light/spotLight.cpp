#include "spotLight.h"

	SpotLight::SpotLight(Renderer* render) : PointLight(render)
	{
		direction = glm::vec3(0.f);
		cutOff = 0.f;
		outerCutOff = 0.f;

		uniformDirection = 0;
		uniformCutOff = 0;
		uniformOuterCutOff = 0;
	}

	SpotLight::~SpotLight()
	{
	}

	void SpotLight::Init(int index)
	{
		std::string indexSTR = std::to_string(index).c_str();
		_renderer->SetUniform(uniformColor, ("spotLight[" + indexSTR + "].pointLight.color").c_str());
		_renderer->SetUniform(uniformPosition, ("spotLight[" + indexSTR + "].pointLight.position").c_str());
		_renderer->SetUniform(uniformAmbient, ("spotLight[" + indexSTR + "].pointLight.ambient").c_str());
		_renderer->SetUniform(uniformDiffuse, ("spotLight[" + indexSTR + "].pointLight.diffuse").c_str());
		_renderer->SetUniform(uniformSpecular, ("spotLight[" + indexSTR + "].pointLight.specular").c_str());
		_renderer->SetUniform(uniformConstant, ("spotLight[" + indexSTR + "].pointLight.constant").c_str());
		_renderer->SetUniform(uniformLinear, ("spotLight[" + indexSTR + "].pointLight.linear").c_str());
		_renderer->SetUniform(uniformQuadratic, ("spotLight[" + indexSTR + "].pointLight.quadratic").c_str());
		_renderer->SetUniform(uniformDirection, ("spotLight[" + indexSTR + "].direction").c_str());
		_renderer->SetUniform(uniformCutOff, ("spotLight[" + indexSTR + "].cutOff").c_str());
		_renderer->SetUniform(uniformOuterCutOff, ("spotLight[" + indexSTR + "].outerCutOff").c_str());
		_renderer->SetUniform(uniformEnabled, ("spotLight[" + indexSTR + "].enabled").c_str());
	}

	void SpotLight::UseLight()
	{
		_renderer->UseShader();
		_renderer->UpdateLight(uniformColor, color.GetColor());
		_renderer->UpdateLight(uniformDirection, direction);
		_renderer->UpdateLight(uniformPosition, transform.position);
		_renderer->UpdateLight(uniformAmbient, ambient);
		_renderer->UpdateLight(uniformDiffuse, diffuse);
		_renderer->UpdateLight(uniformSpecular, specular);
		_renderer->UpdateFloatValue(uniformConstant, constant);
		_renderer->UpdateFloatValue(uniformLinear, linear);
		_renderer->UpdateFloatValue(uniformQuadratic, quadratic);
		_renderer->UpdateFloatValue(uniformCutOff, cutOff);
		_renderer->UpdateFloatValue(uniformOuterCutOff, outerCutOff);
		_renderer->UpdateBoolValue(uniformEnabled, enabled);
		_renderer->CleanShader();
	}

	void SpotLight::SetDirection(glm::vec3 direction)
	{
		this->direction = direction;
	}

	void SpotLight::SetCutOff(float cutOff)
	{
		this->cutOff = cos(glm::radians(cutOff));
	}

	void SpotLight::SetOuterCutOff(float outerCutOff)
	{
		this->outerCutOff = cos(glm::radians(outerCutOff));
	}

	glm::vec3 SpotLight::GetDirection()
	{
		return direction;
	}

	float SpotLight::GetCutOff()
	{
		return cutOff;
	}

	float SpotLight::GetOuterCutOff()
	{
		return outerCutOff;
	}
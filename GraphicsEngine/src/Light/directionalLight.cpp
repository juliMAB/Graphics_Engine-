#include "directionalLight.h"


	DirectionalLight::DirectionalLight(Renderer* render) : Light(render)
	{
		direction = glm::vec3(0.f);
		uniformDirection = 0;
	}

	DirectionalLight::~DirectionalLight()
	{
	}

	void DirectionalLight::Init()
	{
		_renderer->SetUniform(uniformColor, "directionalLight.color");
		_renderer->SetUniform(uniformDirection, "directionalLight.direction");
		_renderer->SetUniform(uniformAmbient, "directionalLight.ambient");
		_renderer->SetUniform(uniformDiffuse, "directionalLight.diffuse");
		_renderer->SetUniform(uniformSpecular, "directionalLight.specular");
		_renderer->SetUniform(uniformEnabled, "directionalLight.enabled");
	}

	void DirectionalLight::UseLight()
	{
		_renderer->UseShader();
		_renderer->UpdateLight(uniformColor, color.GetColor());
		_renderer->UpdateLight(uniformDirection, direction);
		_renderer->UpdateLight(uniformAmbient, ambient);
		_renderer->UpdateLight(uniformDiffuse, diffuse);
		_renderer->UpdateLight(uniformSpecular, specular);
		_renderer->UpdateBoolValue(uniformEnabled, enabled);
		_renderer->CleanShader();
	}

	void DirectionalLight::SetDirection(glm::vec3 direction)
	{
		this->direction = direction;
	}

	glm::vec3 DirectionalLight::GetDirection()
	{
		return direction;
	}

#include "light.h"


	Light::Light(Renderer* render) : Entity(render)
	{
		_color = color::RGBA();
		ambient = glm::vec3(0.f);
		diffuse = glm::vec3(0.f);
		specular = glm::vec3(0.f);
		enabled = true;

		_uniformColorLight = 0;
		_locationPosition = 0;
		_uniformAmbient = 0;
		_uniformDiffuse = 0;
		_uniformSpecular = 0;
		SetUniforms();
	}
	void Light::SetUniforms()
	{
		_renderer->SetUniform(_uniformPositionLight, "lightPos");
		_renderer->SetUniform(_uniformColorLight, "lightColor");
		_renderer->SetUniform(_uniformAmbient, "light.ambient");
		_renderer->SetUniform(_uniformDiffuse, "light.diffuse");
		_renderer->SetUniform(_uniformSpecular, "light.specular");
		_renderer->SetUniform(_uniformAmbientStrength, "ambientStrength");
		
	}

	void Light::UpdateLight()
	{
		_renderer->UseShader();
		_renderer->UpdateVec3(_uniformColorLight, _color.GetColorV3());
		_renderer->UpdateVec3(_uniformPositionLight, getPos());
		_renderer->UpdateVec3(_uniformAmbient, ambient);
		_renderer->UpdateVec3(_uniformDiffuse, diffuse);
		_renderer->UpdateVec3(_uniformSpecular, specular);
		_renderer->UpdateFloatValue(_uniformAmbientStrength, ambientStrength);
		_renderer->CleanShader();
	}
	Light::~Light()
	{
	}

	void Light::SetAmbientStrength(float value)
	{
		ambientStrength = value;
	}

	void Light::SetAmbient(glm::vec3 ambient)
	{
		this->ambient = ambient;
	}

	void Light::SetDiffuse(glm::vec3 diffuse)
	{
		this->diffuse = diffuse;
	}

	void Light::SetSpecular(glm::vec3 specular)
	{
		this->specular = specular;
	}

	void Light::SetEnabled(bool enabled)
	{
		this->enabled = enabled;
	}

	glm::vec3 Light::GetAmbient()
	{
		return ambient;
	}

	glm::vec3 Light::GetDiffuse()
	{
		return diffuse;
	}

	glm::vec3 Light::GetSpecular()
	{
		return specular;
	}

	bool Light::IsEnabled()
	{
		return enabled;
	}
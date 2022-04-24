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
		uniformDiffuse = 0;
		uniformSpecular = 0;
		uniformEnabled = 0;
		SetUniforms();
	}
	void Light::SetUniforms()
	{
		_renderer->SetUniform(_uniformPositionLight, "lightPos");
		_renderer->SetUniform(_uniformColorLight, "lightColor");
		_renderer->SetUniform(_uniformAmbient, "ambientStrength");
	}
	void Light::SetLight(glm::vec3 pos, glm::vec3 color ,float ambientStrength)
	{
		this->SetPos(pos);
		this->_color.SetColor(color);
		this->ambientStrength = ambientStrength;
		UpdateLight();
	}
	void Light::UpdateLight()
	{
		_renderer->SetLight(_uniformColorLight, _uniformPositionLight, _uniformAmbient, _color.GetColorV3(), getPos(), ambientStrength);
		std::cout << "pos: " << getPos().r <<","<< getPos().g <<","<< getPos().b << std::endl;
	}
	Light::~Light()
	{
	}

	void Light::SetAmbient(glm::vec3 ambient)
	{
		this->ambient = ambient;
	}
	void Light::SetAmbientStrength(float ambient)
	{
		this->ambientStrength = ambient;
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
#include "light.h"


Light::Light() {}

Light::Light(Renderer* render) : Entity(render)
	{
		_color = color::RGBA();
		ambient = glm::vec3(0.f);
		diffuse = glm::vec3(0.f);
		specular = glm::vec3(0.f);

		_locationPosition = 0;
		_uniformAmbient = 0;
		_uniformDiffuse = 0;
		_uniformSpecular = 0;
		SetUniforms();
	}
	void Light::SetUniforms()
	{
		_renderer->SetUniform(_uniformAmbient, "light.ambient");
		_renderer->SetUniform(_uniformDiffuse, "light.diffuse");
		_renderer->SetUniform(_uniformSpecular, "light.specular");
		
	}
	void Light::SetUniforms(std::string v)
	{
		_renderer->SetUniform(_uniformAmbient, (v+".ambient").c_str());
		_renderer->SetUniform(_uniformDiffuse, (v+".diffuse").c_str());
		_renderer->SetUniform(_uniformSpecular, (v+".specular").c_str());

	}

	void Light::UpdateLight()
	{
		_renderer->UseShader();

		_renderer->UpdateVec3(_uniformAmbient, ambient);
		_renderer->UpdateVec3(_uniformDiffuse, diffuse);
		_renderer->UpdateVec3(_uniformSpecular, specular);

		_renderer->CleanShader();
	}
	Light::~Light()
	{
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

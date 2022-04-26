#include "material.h"


	Material::Material(Renderer* render)
	{
		this->render = render;

		material.Shiness = 0.f;
		material.ambient = glm::vec3(0.f);
		material.diffuse = glm::vec3(0.f);
		material.specular = glm::vec3(0.f);

		_uniformShininess = 0;
		_uniformAmbient = 0;
		_uniformDiffuse = 0;
		_uniformSpecular = 0;
		useMaterial = true;
	}

	Material::~Material()
	{
	}

	void Material::Init()
	{
		render->SetUniform(_uniformShininess, "material.shininess");
		render->SetUniform(_uniformAmbient, "material.ambient");
		render->SetUniform(_uniformDiffuse, "material.diffuse");
		render->SetUniform(_uniformSpecular, "material.specular");
		render->SetUniform(_uniformUseMaterial, "affectedMaterial");
		render->UpdateBoolValue(_uniformUseMaterial, useMaterial);
	}

	void Material::UpdateMaterial()
	{
		render->UpdateFloatValue(_uniformShininess, material.Shiness);
		render->UpdateVec3(_uniformAmbient, material.ambient);
		render->UpdateVec3(_uniformDiffuse, material.diffuse);
		render->UpdateVec3(_uniformSpecular, material.specular);
	}

	void Material::SetShininess(float shininess)
	{
		this->material.Shiness = shininess;
	}

	void Material::SetAmbient(glm::vec3 ambient)
	{
		this->material.ambient = ambient;
	}

	void Material::SetDiffuse(glm::vec3 diffuse)
	{
		this->material.diffuse = diffuse;
	}

	void Material::SetSpecular(glm::vec3 specular)
	{
		this->material.specular = specular;
	}

	void Material::SetMaterial(MaterialS mat)
	{
		this->material = mat;
	}

	float Material::GetShininess()
	{
		return material.Shiness;
	}

	glm::vec3 Material::GetAmbient()
	{
		return material.ambient;
	}

	glm::vec3 Material::GetDiffuse()
	{
		return material.diffuse;
	}

	glm::vec3 Material::GetSpecular()
	{
		return material.specular;
	}

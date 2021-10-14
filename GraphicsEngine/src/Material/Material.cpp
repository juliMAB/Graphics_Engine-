#include "Material.h"
#include "../GLEW/glew.h"

	Material::Material(Renderer* rend) {
		_shininess = 0.0f;
		_ambient = glm::vec3(1.0f, 1.0f, 1.0f);
		_diffuse = glm::vec3(0.0f, 0.0f, 0.0f);
		_specular = glm::vec3(0.0f, 0.0f, 0.0f);
		_renderer = rend;
		_uniformShininess = glGetUniformLocation(_renderer->GetShader(), "material.shininess");
		_uniformAmbient = glGetUniformLocation(_renderer->GetShader(), "material.ambient");
		_uniformDiffuse = glGetUniformLocation(_renderer->GetShader(), "material.diffuse");
		_uniformSpecular = glGetUniformLocation(_renderer->GetShader(), "material.specular");
	}
	Material::~Material() {}
	void Material::SetAmbient(glm::vec3 amb) {
		_ambient = amb;
	}
	void Material::SetDiffuse(glm::vec3 diff) {
		_diffuse = diff;
	}
	void Material::SetSpecular(glm::vec3 spec) {
		_specular = spec;
	}
	void Material::SetShininess(float s) {
		_shininess = s;
	}
	glm::vec3 Material::GetAmbient() {
		return _ambient;
	}
	glm::vec3 Material::GetDiffuse() {
		return _diffuse;
	}
	glm::vec3 Material::GetSpecular() {
		return _specular;
	}
	float Material::GetShininess() {
		return _shininess;
	}
	uint Material::GetUniformShininess() {
		return _uniformShininess;
	}
	uint Material::GetUniformAmbient() {
		return _uniformAmbient;
	}
	uint Material::GetUniformDiffuse() {
		return _uniformDiffuse;
	}
	uint Material::GetUniformSpecular() {
		return _uniformSpecular;
	}

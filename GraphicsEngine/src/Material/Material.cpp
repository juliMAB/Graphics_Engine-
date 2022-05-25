#include "material.h"


	Material::Material(Renderer* render)
	{
		this->render = render;
		material = new MaterialS();
		material->Shiness = 0.f;

		_uniformShininess = 0;
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
		render->SetUniform(_uniformDiffuse, "material.diffuse1");
		render->SetUniform(_uniformSpecular, "material.specular1");
		render->SetUniform(_uniformUseMaterial, "affectedMaterial");
	}

	void Material::UpdateMaterial()
	{
		if(useMaterial)
		render->UpdateFloatValue(_uniformShininess, material->Shiness);
		render->UpdateInt(_uniformDiffuse, 0);
		render->UpdateInt(_uniformSpecular, 1);
	}

	void Material::SetShininess(float shininess)
	{
		this->material->Shiness = shininess;
	}


	void Material::SetDiffuse(MyTexture* diffuse)
	{
		this->material->diffuse = diffuse;
	}

	void Material::SetSpecular(MyTexture* specular)
	{
		this->material->specular = specular;
	}


	void Material::SetMaterial(MaterialS* mat)
	{
		this->material = mat;
	}

	float Material::GetShininess()
	{
		return material->Shiness;
	}

	MyTexture* Material::GetDiffuse()
	{
		return material->diffuse;
	}

	MyTexture* Material::GetSpecular()
	{
		return material->specular;
	}

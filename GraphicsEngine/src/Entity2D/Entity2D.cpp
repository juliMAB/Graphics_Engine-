#include "Entity2D.h"
namespace JuliEngine
{

	void Entity2D::UpdateShader()
	{
		_renderer->UpdateMVP(getTransform()->getmodel());
	}
	void Entity2D::AffectedLight(bool value)
	{
		affectedLight = value;
	}

	void Entity2D::Draw()
	{
		Entity2::Draw();
		if (_material != nullptr)
		{
			_material->UpdateMaterial();
		}

		_renderer->Draw(_VAO, _VBO, _EBO, vertices, tam, vertexs);
	}

	Entity2D::Entity2D(Renderer* render) : Entity2(render)
	{
		_material = nullptr;

		_VAO = 0;
		_VBO = 0;
		_EBO = 0;
		tam = 0;
		vertexs = 0;
		vertices = 0;

		useTexture = false;
		useMaterial = false;
		affectedLight = true;
		SetUniforms();
	}

	Entity2D::~Entity2D()
	{
	}
	void Entity2D::UpdateMaterial()
	{
		if (useMaterial)
		_material->UpdateMaterial();
	}

	void Entity2D::SetMateria(MaterialS* mat)
	{
		useMaterial = true;
		_material = new Material(_renderer);
		_material->Init();
		_material->SetMaterial(mat);
		_material->UpdateMaterial();
	}

	void Entity2D::SetUniforms()
	{
		Entity2::SetUniforms();
		_renderer->SetUniform(_uniformColor, "color");
		_renderer->SetUniform(_uniformAplha, "alpha");
	}
}

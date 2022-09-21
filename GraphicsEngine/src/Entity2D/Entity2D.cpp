#include "Entity2D.h"
namespace JuliEngine
{
	void Entity2D::Draw()
	{
		_renderer->Draw(_VAO, _VBO, _EBO, vertices, tam, vertexs);
		Entity2::draw();
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
	}

	Entity2D::~Entity2D()
	{
	}


	void Entity2D::SetUniforms()
	{
		Entity2::SetUniforms();
	}
}
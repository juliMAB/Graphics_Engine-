#include "Entity3D.h"

Entity3D::Entity3D()
{

}

Entity3D::Entity3D(Renderer* render, std::string path)
{
	_renderer = render;

	meshes = Importer::loadModel(path);
}

Entity3D::~Entity3D()
{
}

void Entity3D::draw()
{
	_renderer->UpdateMVP(matrix.model);

	for (int i = 0; i < meshes.size(); i++)
	{
		_renderer->DrawMesh(meshes[i].vertices, meshes[i].indices, meshes[i].textures, meshes[i].VAO);
	}
}

void Entity3D::deinit()
{
}
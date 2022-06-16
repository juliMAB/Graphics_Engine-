#include "Entity3D.h"

namespace JuliEngine
{
	Entity3D::Entity3D(Renderer* render, std::string path) : Entity2(render)
	{
		Setname("Entity3D");
		_renderer = render;
	#if IMPORTER
		meshes = Importer::loadModel(path);
	#endif // IMPORTER
	}

	void Entity3D::draw()
	{
		SetUniforms();
		_renderer->UpdateMVP(getTransform().getmodel());

		for (int i = 0; i < meshes.size(); i++)
		{
			_renderer->DrawMesh(meshes[i].vertices, meshes[i].indices, meshes[i].textures, meshes[i].VAO);
		}
	}
}

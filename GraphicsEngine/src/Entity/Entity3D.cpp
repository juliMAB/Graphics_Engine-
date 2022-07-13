#include "Entity3D.h"

namespace JuliEngine
{
	std::list<Entity3D*> Entity3D::entitys3dList;
	Entity3D::Entity3D(Renderer* render, std::string path)
	{
		model = new Model(render);
	#if IMPORTER
		Importer2 inp;
		inp.loadModel(model, path);
	#endif // IMPORTER
		entitys3dList.push_back(this);
	}
	Entity3D::~Entity3D()
	{
		entitys3dList.remove(this);
	}
}

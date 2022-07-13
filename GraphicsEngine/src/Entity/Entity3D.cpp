#include "Entity3D.h"

namespace JuliEngine
{
	Entity3D::Entity3D(Renderer* render, std::string path)
	{
		model = new Model(render);
	#if IMPORTER
		Importer2 inp;
		inp.loadModel(model, path);
	#endif // IMPORTER
	}
}

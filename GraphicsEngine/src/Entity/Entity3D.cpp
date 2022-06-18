#include "Entity3D.h"

namespace JuliEngine
{
	Entity3D::Entity3D(Renderer* render, std::string path) : Entity2(render)
	{
		model = new Model2(render, false);
		Setname("Entity3D");
		_renderer = render;
	#if IMPORTER
		Importer2::loadModel(model,path);
	#endif // IMPORTER
	}

	void Entity3D::draw()
	{
		SetUniforms();
		_renderer->UpdateMVP(getTransform().getmodel());
		model->Draw();
	}
}

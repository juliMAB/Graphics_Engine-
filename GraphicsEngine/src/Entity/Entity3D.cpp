#include "Entity3D.h"

namespace JuliEngine
{
	Entity3D::Entity3D(Renderer* render, std::string path) : Entity2(render)
	{
		setName("ENTITY3d ");
		model = new Model2(render, false);
		model->setName("MODELO ");
		model->getTransform()->setparent(this->getTransform());
	#if IMPORTER
		Importer2::loadModel(model,path);
	#endif // IMPORTER
	}

	void Entity3D::draw()
	{
		if (getactive())
		{
			model->Draw();
		}
	}
	void Entity3D::draw(Frustum* frustum)
	{
		if (getactive())
		{
			model->drawSelfAndChild(frustum);
		}
	}
}

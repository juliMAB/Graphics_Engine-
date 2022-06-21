#include "Entity3D.h"

namespace JuliEngine
{
	Entity3D::Entity3D(Renderer* render, std::string path) : Entity2(render)
	{
		model = new Model2(render, false);
		model->setName("MODELO ");
		model->getTransform()->setparent(this->getTransform());
	#if IMPORTER
		Importer2::loadModel(model,path);
	#endif // IMPORTER
	}

	void Entity3D::draw()
	{
		//_renderer->UpdateMVP(getTransform()->getmodel());
		model->Draw();
	}
}

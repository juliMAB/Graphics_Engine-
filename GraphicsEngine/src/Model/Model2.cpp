#include "Model2.h"
namespace JuliEngine
{
	list<Model2*> Model2::listModel;


	void Model2::generateAABB()
	{
		glm::vec3 minAABB = glm::vec3(std::numeric_limits<float>::max());
		glm::vec3 maxAABB = glm::vec3(std::numeric_limits<float>::min());
	
		for (std::list<Mesh2*>::iterator it = meshes.begin(); it != meshes.end(); it++)
		{
			MeshData* data = (**it).data;
			for (auto&& vertex : data->vertices)
			{
				minAABB.x = std::min(minAABB.x, vertex.Position.x);
				minAABB.y = std::min(minAABB.y, vertex.Position.y);
				minAABB.z = std::min(minAABB.z, vertex.Position.z);
	
				maxAABB.x = std::max(maxAABB.x, vertex.Position.x);
				maxAABB.y = std::max(maxAABB.y, vertex.Position.y);
				maxAABB.z = std::max(maxAABB.z, vertex.Position.z);
			}
		}
		volume = new AABB(minAABB, maxAABB);
	}
	void Model2::Draw()
	{
		if (getactive())
		{
			for (std::list<Mesh2*>::iterator it = meshes.begin(); it != meshes.end(); it++)
				if ((*it)->getactive())
					(*it)->Draw();
		}
	}
	void Model2::drawSelfAndChild(Frustum* frustum)
	{
		if (volume->isOnFrustum(frustum, getTransform()))
		{
			_renderer->UpdateModel(getTransform()->getModelMatrix());

			Draw();
		}

		for (auto&& child : getTransform()->getChilds())
		{
			if (child->getEntity()->getModelPtr()!=nullptr)
			{
				child->getEntity()->getModelPtr()->drawSelfAndChild(frustum);
			}
		}
	}
}

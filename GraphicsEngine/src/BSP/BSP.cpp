#include "bsp.h"

namespace JuliEngine
{
	BSP::BSP()
	{
		render = nullptr;
		camera = nullptr;

		entities = std::list<Entity2*>();
		planes = std::list<plane*>();
	}

	BSP::BSP(Renderer* render, Camera2* camera)
	{
		this->render = render;
		this->camera = camera;

		entities = std::list<Entity2*>();
		planes = std::list<plane*>();
	}

	void BSP::Draw()
	{
		for (std::list<Entity2*>::iterator it2 = entities.begin(); it2 != entities.end(); ++it2)
		{
			bool dibujable = true;
			for (std::list<plane*>::iterator it = planes.begin(); it != planes.end(); ++it)
			{
				if (!AskBox((*it), (*it2)))
				{
					dibujable = false;
					break;
				}
			}
			if (dibujable)
				(*it2)->draw();
		}
	}

	bool BSP::AskBox(plane* plan, Entity2* entity)
	{
		if (entity->getVolume() == nullptr)
		{
			return false;
			cout << "esta entidad no tiene volumen: " + entity->getName() << endl;
		}
		bool sameSide=false;
		vec3 center = entity->getVolume()->center;
		vec3 extend = entity->getVolume()->extents;
		vec3 extremo[8] = {
			center + vec3(extend.x,extend.y,extend.z),
			center + vec3(extend.x,extend.y,-extend.z),
			center + vec3(extend.x,-extend.y,extend.z),
			center + vec3(-extend.x,extend.y,extend.z),
			center + vec3(extend.x,-extend.y,-extend.z),
			center + vec3(-extend.x,-extend.y,extend.z),
			center + vec3(-extend.x,extend.y,-extend.z),
			center + vec3(-extend.x,-extend.y,-extend.z),
		};
		for (int i = 0; i < 8; i++)
			if ((plan->GetSide(camera->getPos()) == plan->GetSide(extremo[i])))
				return true;
		return false;
	}

	void BSP::DeInit()
	{
		entities.clear();

		planes.clear();
	}

	void BSP::AddEntity(Entity2* entity)
	{
		entities.push_back(entity);
	}

	void BSP::AddPlane(glm::vec3 position, glm::vec3 normal)
	{
		plane* plan = new plane(normal, position);

		planes.push_back(plan);
	}

	void BSP::AddPlane(plane* plan)
	{
		planes.push_back(plan);
	}
	void BSP::AddPlane(Entity2* entity)
	{
		if (entity->getName().find("bsp") != std::string::npos)
		{
			plane* plan = new JuliEngine::plane(entity->GetFront(), entity->getPos());
			planes.push_back(plan);
		}
	}

	void BSP::TogglePlaneStatus()
	{
		//for (std::list<plane*>::iterator it = planes.begin(); it != planes.end(); ++it)
		//{
		//	(*it)->SwitchCanDrawStatus();
		//}
	}

	//void BSP::UpdateNodeVolume(Entity2* node)
	//{
	//	bool drawEntity = true;
	//
	//	for (std::list<PlaneBSP*>::iterator itP = planes.begin(); itP != planes.end(); ++itP)
	//	{
	//		if (node->GetGlobalVolume()->IsOnPlane(*(*itP)->plane) != (*itP)->plane->GetSide(camera->GetPos()))
	//		{
	//			drawEntity = false;
	//			break;
	//		}
	//	}
	//	node->visible = drawEntity;
	//
	//	std::list<Entity*> nodes = node->GetNodes();
	//	if (!nodes.empty())
	//	{
	//		for (std::list<Entity*>::iterator itN = nodes.begin(); itN != nodes.end(); ++itN)
	//		{
	//			UpdateNodeVolume((*itN));
	//		}
	//	}
	//}
}
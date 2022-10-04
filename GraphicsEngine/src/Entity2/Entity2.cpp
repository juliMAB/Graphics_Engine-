#include "Entity2.h"
#include "Juli/Jinterface.h"
namespace JuliEngine
{
	int Entity2::CuantityEntitys = 0;
	std::list<Entity2*> Entity2::EntitysLists;
	Entity2::Entity2(Renderer* renderer) : GameObject(this)
	{
		_renderer = renderer;
		_locationPosition =0;
		_locationNormal	  =0;
		_locationTexCoord =0;
		_color = glm::vec3(1, 1, 1);
		EntitysLists.push_front(this);
		 SetnameOBJ("Entity " + std::to_string(CuantityEntitys));
		 setName("Entity " + std::to_string(CuantityEntitys));
		 AddDescription("-> || " + getName() + " || ");
		CuantityEntitys++;
		meshes = vector<Mesh*>();
		parent = nullptr;
		volume = nullptr;
	}
	Entity2::~Entity2()
	{
		EntitysLists.remove(this);
	}

	void Entity2::SetPos(glm::vec3 pos)
	{
		getTransform()->setPos(pos);
	}

	void Entity2::SetPos(float x, float y, float z)
	{
		SetPos(vec3(x, y, z));
	}

	void Entity2::SetPos(float x, float y)
	{
		SetPos(vec3(x, y, getPos().z));
	}

	void Entity2::SetPos(glm::vec2 pos)
	{
		SetPos(vec3(pos.x, pos.y, getPos().z));
	}

	void Entity2::SetRot(glm::vec3 rot)
	{
		getTransform()->setRot(rot);
	}

	void Entity2::SetRotX(float x)
	{
		vec3 v = getRot();
		SetRot(x, v.y, v.z);
	}

	void Entity2::SetRotY(float y)
	{
		vec3 v = getRot();
		SetRot(v.x, y, v.z);
	}

	void Entity2::SetRotZ(float z)
	{
		vec3 v = getRot();
		SetRot(v.x, v.y, z);
	}

	void Entity2::SetRot(float x, float y, float z)
	{
		SetRot(vec3(x, y, z));
	}

	void Entity2::SetScale(glm::vec3 v)
	{
		getTransform()->setScl(v);
	}

	void Entity2::SetScale(float x, float y)
	{
		SetScale(vec3(x, y, getScale().z));
	}

	void Entity2::SetScale(float x, float y, float z)
	{
		SetScale(vec3(x, y, z));
	}

	void Entity2::SetScaleAllSame(float v)
	{
		SetScale(vec3(v, v, v));
	}

	void Entity2::SetScaleMulty(float v)
	{
		vec3 s = getScale();
		SetScale(s.x * v, s.y * v, s.z * v);
	}

	glm::vec3 Entity2::getPos()
	{
		return getTransform()->getpos();
	}

	glm::vec3 Entity2::getRot()
	{
		return getTransform()->getrot();
	}

	glm::vec3 Entity2::getScale()
	{
		return getTransform()->getscl();
	}

	glm::vec3 Entity2::GetUp()
	{
		return getTransform()->getUp();
	}

	glm::vec3 Entity2::GetFront()
	{
		return getTransform()->getForward();
	}

	glm::vec3 Entity2::GetRight()
	{
		return getTransform()->getRight();
	}

	void Entity2::SetMatrix(glm::mat4 mat)
	{
		getTransform()->setMatrix(mat);
	}

	Entity2* Entity2::GetNode(std::string nodeName)
	{
		if (getName() == nodeName)
		{
			return this;
		}

		if (children.size() > 0)
		{
			Entity2* node = nullptr;
			for (int i = 0; i < children.size(); i++)
			{
				node = children[i]->GetNode(nodeName);

				if (node != nullptr) break;
			}
			return node;
		}
		return nullptr;
	}
	Entity2* Entity2::GetNode(std::string nodeName, std::string data)
	{
		if (getName().find(nodeName)!= -1 && getName().find(data)!=-1)
		{
			return this;
		}

		if (children.size() > 0)
		{
			Entity2* node = nullptr;
			for (int i = 0; i < children.size(); i++)
			{
				node = children[i]->GetNode(nodeName);

				if (node != nullptr) break;
			}
			return node;
		}
		return nullptr;
	}

	void Entity2::DebugInfo()
	{
		cout << endl << "-----ExampleDebugInfoEntity2------" << endl;
		Transform* transform = getTransform();
		cout << "pos: " + VecToString::vec3toString(transform->getpos())		<< std::endl;
		cout << "rot: " + VecToString::vec3toString(transform->getrot())		<< std::endl;
		cout << "sca: " + VecToString::vec3toString(transform->getscl())		<< std::endl;
		cout << "for: " + VecToString::vec3toString(transform->getForward())	<< std::endl;
		cout << "up:  " + VecToString::vec3toString(transform->getUp())			<< std::endl;
		cout << "rig: " + VecToString::vec3toString(transform->getRight())		<< std::endl;
	}
	void Entity2::Update()
	{
		//updateSelfAndChild();
	}

	void Entity2::SetUniforms()
	{
		_renderer->SetLocation(_locationPosition, "aPos");
		_renderer->SetLocation(_locationTexCoord, "aTex");
		_renderer->SetLocation(_locationNormal, "aNor");
		_renderer->SetUniform(_uniformColor, "color");
	}
	bool Entity2::canDrawThisFrame()
	{
		return drawThisFrame;
	}
	void Entity2::SetMeshes(vector<Mesh*> meshes)
	{
		this->meshes = meshes;
	}
	void Entity2::SetParent(Entity2* parent)
	{
		this->parent = parent;
	}
	void Entity2::setChildren(vector<Entity2*> children)
	{
		this->children = children;
	}
	void Entity2::AddChildren(Entity2* children)
	{
		this->children.push_back(children);
	}
	void Entity2::draw()
	{
		if (volume!=NULL && meshes.size() > 0)
		{
			cout << "Si" << endl;
			drawThisFrame = true;
		}
		if (drawThisFrame && volume != NULL && volume->isOnFrustum(getTransform()->getModel()))
		{
			if (meshes.size() > 0)
			{
				_renderer->UpdateModel(getTransform()->getModel());

				for (int i = 0; i < meshes.size(); i++)
				{
					_renderer->drawMesh(meshes[i]->vertexs, meshes[i]->indexes, meshes[i]->textures, meshes[i]->VAO, _color);
				}
			}

			for (int i = 0; i < children.size(); i++)
			{
				children[i]->draw();
			}
		}
	}
	//void Entity2::setDraw()
	//{
	//	drawThisFrame = false;
	//
	//	for (int i = 0; i < getChildren().size(); i++)
	//	{
	//		//al child le paso la matriz del padere, para que en la proxima valor de i, ya se pase la posicion actualizada.
	//		getChildren()[i]->setWorldModelWithParentModel(getTransform()->getWorldModel());
	//		//con la nueva posicion del padre, se hace recursiva esta funcion en cada hijo, hasta no tener hijo.
	//		getChildren()[i]->setDraw();
	//		//una vez que llege al ultimo hijo, se comienza a actualizar el aabb.
	//		addBoundsToAABB(getChildren()[i]->getLocalAABB());
	//	}
	//	//despues de actualizar los aabb y las posiciones procede a dibujarse siempre que se encuentre en el frustrum.
	//	if (!drawThisFrame && meshes.size() > 0 && volume!=NULL && volume->isOnFrustum(getTransform()->getWorldModel()))
	//	{
	//		drawThisFrame = true;
	//		draw();
	//	}
	//	if (children.size()>0)
	//	{
	//		for (int i = 0; i < children.size(); i++)
	//			if (children[i]->drawThisFrame)
	//			{
	//				drawThisFrame = true;
	//				break;
	//			}
	//	}
	//}
	void Entity2::Init()
	{
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->Init();
		}
		generateAABB();
	}

	void Entity2::generateAABB()
	{
		if (meshes.size() > 0)
		{
			glm::vec3 minAABB = glm::vec3(std::numeric_limits<float>::max());
			glm::vec3 maxAABB = glm::vec3(std::numeric_limits<float>::min());

			for (int i = 0; i < meshes.size(); i++)
			{
				Mesh* mesh = meshes[i];
				for (int j = 0; j < mesh->vertexs.size(); j++)
				{
					Vertex vertex = mesh->vertexs[j];

					minAABB.x = glm::min(minAABB.x, vertex.Position.x);
					minAABB.y = glm::min(minAABB.y, vertex.Position.y);
					minAABB.z = glm::min(minAABB.z, vertex.Position.z);

					maxAABB.x = glm::max(maxAABB.x, vertex.Position.x);
					maxAABB.y = glm::max(maxAABB.y, vertex.Position.y);
					maxAABB.z = glm::max(maxAABB.z, vertex.Position.z);
				}
			}

			volume = new JuliEngine::aabb(minAABB, maxAABB);
		}
	}

	void Entity2::addBoundsToAABB(vector<glm::vec3> childAABB)
	{
		if (childAABB.size() < 1)
		{
			return;
		}
		else if (localAABB.size() < 1)
		{
			localAABB.clear();
			localAABB.push_back(childAABB[0]);
			localAABB.push_back(childAABB[1]);

			aabb.clear();
			aabb.push_back(childAABB[0]);
			aabb.push_back(childAABB[1]);

			return;
		}

		localAABB.clear();
		localAABB.push_back(aabb[0]);
		localAABB.push_back(aabb[1]);

		if (childAABB[0].x < localAABB[0].x) localAABB[0].x = childAABB[0].x;
		if (childAABB[1].x > localAABB[1].x) localAABB[1].x = childAABB[1].x;
		if (childAABB[0].y < localAABB[0].y) localAABB[0].y = childAABB[0].y;
		if (childAABB[1].y > localAABB[1].y) localAABB[1].y = childAABB[1].y;
		if (childAABB[0].z < localAABB[0].z) localAABB[0].z = childAABB[0].z;
		if (childAABB[1].z > localAABB[1].z) localAABB[1].z = childAABB[1].z;
	}

	vector<glm::vec3> Entity2::getLocalAABB()
	{
		return localAABB;
	}
}

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
		meshes = vector<Mesh>();
	}
	Entity2::~Entity2()
	{
		EntitysLists.remove(this);
	}

	void Entity2::SetPos(glm::vec3 pos)
	{
		if (getisStatic())
			return;
		getTransform()->setposition(pos);
	}

	void Entity2::DebugInfo()
	{
		cout << endl << "-----ExampleDebugInfoEntity2------" << endl;
		Transform* transform = getTransform();
		cout << "pos: " + VecToString::vec3toString(transform->getposition())		<< std::endl;
		cout << "rot: " + VecToString::vec3toString(transform->geteulerAngles())		<< std::endl;
		cout << "sca: " + VecToString::vec3toString(transform->getlocalScale())		<< std::endl;
		cout << "for: " + VecToString::vec3toString(transform->getForward())			<< std::endl;
		cout << "up:  " + VecToString::vec3toString(transform->getUp())				<< std::endl;
		cout << "rig: " + VecToString::vec3toString(transform->getRight())			<< std::endl;
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
	void Entity2::SetMeshes(vector<Mesh> meshes)
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
	void Entity2::setDraw()
	{
		drawThisFrame = false;

		for (int i = 0; i < getChildren().size(); i++)
		{
			getChildren()[i]->setWorldModelWithParentModel(worldModel);
			getChildren()[i]->setDraw();
			addBoundsToAABB(getChildren()[i]->getLocalAABB());

			if (getChildren()[i]->canDrawThisFrame())
			{
				drawThisFrame = true;
				draw();
			}
		}

		if (!drawThisFrame && meshes.size() > 0 && volume!=NULL && volume->isOnFrustum(getTransform()->getmodel()))
		{
			drawThisFrame = true;
			draw();
		}
	}
	void Entity2::Init()
	{
		for (int i = 0; i < getChildren().size(); i++)
		{
			children[i]->Init();
		}
		generateAABB();
	}
	void Entity2::setWorldModelWithParentModel(glm::mat4 parentModel)
	{
		this->parentModel = parentModel;

		updateModelMatrix();
	}

	void Entity2::generateAABB()
	{
		if (meshes.size() > 0)
		{
			glm::vec3 minAABB = glm::vec3(std::numeric_limits<float>::max());
			glm::vec3 maxAABB = glm::vec3(std::numeric_limits<float>::min());

			for (int i = 0; i < meshes.size(); i++)
			{
				Mesh mesh = meshes[i];
				for (int j = 0; j < mesh.vertices.size(); j++)
				{
					Vertex vertex = mesh.vertices[j];

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

	void Entity2::updateModelMatrix()
	{
		if (getParent() != NULL)
		{
			localModel = getTransform()->getLocalModelMatrix();
			worldModel = parentModel * localModel;
		}
		else
		{
			worldModel = getTransform()->getLocalModelMatrix();
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
	void Entity2::draw()
	{
		_renderer->UpdateMVP(getTransform()->getModelMatrix());

		for (int i = 0; i < meshes.size(); i++)
		{
			_renderer->drawMesh(meshes[i].vertices, meshes[i].indices, meshes[i].textures, meshes[i].VAO, vec3(1,1,1));
		}
	}
}

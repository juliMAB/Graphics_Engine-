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
		EntitysLists.push_front(this);
		 SetnameOBJ("Entity " + std::to_string(CuantityEntitys));
		 setName("Entity " + std::to_string(CuantityEntitys));
		 AddDescription("-> || " + getName() + " || ");
		CuantityEntitys++;
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
		getTransform()->updateSelfAndChild();
	}

	void Entity2::SetUniforms()
	{
		_renderer->SetLocation(_locationPosition, "aPos");
		_renderer->SetLocation(_locationTexCoord, "aTex");
		_renderer->SetLocation(_locationNormal, "aNor");
		_renderer->SetUniform(_uniformColor, "color");
	}
}

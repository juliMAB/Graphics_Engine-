#include "GameObject.h"

JuliEngine::GameObject::GameObject():Object()
{
	active = true; 
	layer = 0;
	transform =new Transform(this);
	tag = ""; 
	AddDescription("-> ||GameObject|| ");
}
JuliEngine::GameObject::~GameObject()
{
	if (transform != NULL)
	{
		delete transform;
		transform = NULL;
	}
}


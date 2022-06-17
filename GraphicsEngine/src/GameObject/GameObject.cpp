#include "GameObject.h"

JuliEngine::GameObject::GameObject():Object()
{
	active = true; 
	layer = 0;
	transform = Transform(this);
	tag = ""; 
	AddDescription("-> ||GameObject|| ");
};

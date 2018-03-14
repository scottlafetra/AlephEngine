#include "Kinematics.h"


AlephEngine::Kinematics::Kinematics(Entity * entity)
	: Component(entity, Component::Type<Kinematics>()) 
{ 
	myTransform = entity->FetchComponent<Transform>();

	if (myTransform == NULL)
	{
		FatalError("Cannot find transform component for Kinematics to work on.");
	}
}


void AlephEngine::Kinematics::MoveStep()
{
	// TODO: Fill in code here
}

#include "Kinematics.h"


AlephEngine::Kinematics::Kinematics(Entity * entity)
	: Component(entity, Component::Type<Kinematics>()) { }


void AlephEngine::Kinematics::MoveStep()
{
	// TODO: Fill in code here
}

#include "Kinematics.h"
#include "Transform.h"

AlephEngine::Kinematics::Kinematics(Entity * entity)
	: Component(entity, Component::Type<Kinematics>()), mass(1), force(gmtl::Vec<float, 3>(0, 0, 0))
{ 
	myTransform = entity->FetchComponent<Transform>();

	if (myTransform == NULL)
	{
		FatalError("Cannot find transform component for Kinematics to work on.");
	}

	entity->GetScene()->physicsMaster.TrackPhysics(this);
}

AlephEngine::Kinematics::~Kinematics()
{
	entity->GetScene()->physicsMaster.StopTrackingPhysics(this);
}

void AlephEngine::Kinematics::MoveStep()
{
	// TODO: Fill in code here
}

void AlephEngine::Kinematics::AddForce(gmtl::Vec<float, 3> addedForce)
{
	force += addedForce;
}

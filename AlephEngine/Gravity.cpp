#include "Gravity.h"
#include "Transform.h"

AlephEngine::Gravity::Gravity(Entity* entity) :
	Component( entity, Component::Type<Gravity>())
{ 
	if ((myKinematics = entity->FetchComponent<Kinematics>()) == NULL)
	{
		FatalError("Gravity component not attached to entity with Kinematics component.");
	}

	if ((myTransform = entity->FetchComponent<Transform>()) == NULL)
	{
		FatalError("Gravity component not attached to entity with Kinematics component.");
	}
}

void AlephEngine::Gravity::attract(Kinematics & yourKin)
{
	//distanceComponents = m_myKin - yourKin
	Transform* yourTransform = NULL;

	if ((yourTransform = yourKin.GetEntity()->FetchComponent<Transform>()) == NULL)
	{
		Error(yourKin.GetEntity()->GetName() + " does not have a Transform component.");
		return;
	}

	gmtl::Vec<float, 3> direction = (myTransform->GetPosition() + myKinematics->centerOfMass) - (yourTransform->GetPosition() + yourKin.centerOfMass);

	//distance
	float distance = sqrt(pow(direction[0], 2) + pow(direction[1], 2) + pow(direction[2], 2));
	// force kg*m/s/s
	float forceMagnitude = (G * myKinematics->mass * yourKin.mass / pow(distance, 2));

	gmtl::Vec<float, 3> newForce = direction / distance * forceMagnitude;

	myKinematics->AddForce(newForce);
	yourKin.AddForce(newForce * -1.f);
}
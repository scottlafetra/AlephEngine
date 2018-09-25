#include "Gravity.h"
#include "../Core/Transform.h"
#include <iostream>
#include <algorithm>


float AlephEngine::Gravity::G = 6.67 * pow(10, -11);
float AlephEngine::Gravity::maxImpulse = 500;

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

	// No self love here, we should gracefully return
	if (myKinematics == &yourKin)
	{
		return;
	}

	if ((yourTransform = yourKin.GetEntity()->FetchComponent<Transform>()) == NULL)
	{
		Error(yourKin.GetEntity()->GetName() + " does not have a Transform component.");
		return;
	}

	

	gmtl::Vec<float, 3> direction = (myTransform->GetPosition() + myKinematics->centerOfMass) - (yourTransform->GetPosition() + yourKin.centerOfMass);

	//distance
	float distance = sqrt(pow(direction[0], 2) + pow(direction[1], 2) + pow(direction[2], 2));

	// Prevent NaN Errors
	if (distance == 0)
	{
		return;
	}

	// force kg*m/s/s
	float forceMagnitude = (G * myKinematics->mass * yourKin.mass / pow(distance, 2));

	forceMagnitude = std::max(forceMagnitude, (float) (maxImpulse * EngineTime::GetDeltaTime()));

	gmtl::Vec<float, 3> newForce = direction / distance * forceMagnitude;

	myKinematics->AddForce(newForce * -1.f);
	yourKin.AddForce(newForce);
}
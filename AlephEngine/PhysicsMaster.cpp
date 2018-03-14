#include "PhysicsMaster.h"

#include "Kinematics.h"
#include "Transform.h"
#include "EngineTime.h"
#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>

void PhysicsMaster::TrackPhysics(AlephEngine::Kinematics* toAdd)
{
	tracking.push_back(toAdd);
}

void PhysicsMaster::StopTrackingPhysics(AlephEngine::Kinematics* toAdd)
{
	tracking.remove(toAdd);
}

void PhysicsMaster::StepPhysics()
{
	for (AlephEngine::Kinematics* k : tracking)
	{
		gmtl::Vec<float, 3> accel = k->forceTotal;

		accel /= k->mass;

		k->velocity += accel * (float) EngineTime::GetDeltaTime();

		// Move step
		k->myTransform->Move(k->velocity * (float) EngineTime::GetDeltaTime());
	}
}

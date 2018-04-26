#include "PhysicsMaster.h"

#include "Kinematics.h"
#include "Transform.h"
#include "EngineTime.h"
#include "Collision.h"
#include "Gravity.h"
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
		gmtl::Vec<float, 3> accel = k->force;

		accel /= k->mass;

		k->velocity += accel * (float) EngineTime::GetDeltaTime();

		// Move step
		k->myTransform->Move(k->velocity * (float) EngineTime::GetDeltaTime());

		Collider* myCollider = k->GetEntity()->FetchComponent<Collider>();

		if( myCollider != NULL )
		{
			// Handle collisions
			for( AlephEngine::Kinematics* other : tracking )
			{
				if( k == other )
				{
					continue;
				}

				Collider* otherCollider = other->GetEntity()->FetchComponent<Collider>();
				if( otherCollider != NULL )
				{
					Collision* hit = myCollider->checkCollision( *otherCollider );
					if( hit != NULL )
					{/*
						// Resolve hit here
						Gravity::G = 0;
						k->myTransform->Move( gmtl::Vec<float, 3>(
											hit->X_overlap * 1.1,
											hit->Y_overlap * 1.1,
											hit->Z_overlap * 1.1
											));
						k->velocity *= 0;*/
						k->velocity *= 0;
						Gravity::G = 0;
						free( hit );
					}
				}
			}
		}
		

		// Reset
		k->force = gmtl::Vec<float, 3>(0, 0, 0);
	}

	
}

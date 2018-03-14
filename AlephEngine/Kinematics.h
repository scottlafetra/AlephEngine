#pragma once

#include <gmtl/Vec.h>
#include "Component.h"

namespace AlephEngine
{
	class Kinematics : public Component
	{
		friend class PhysicsMaster;

	private:
		// Force totals to be reset at move step
		gmtl::Vec<float, 3> forceTotal;
		
		Transform* myTransform;

		// Moves this Kinematic object
		void MoveStep();

	public:
		Kinematics(Entity* entity);
		
		// meters/second use like vector x, y, z
		gmtl::Vec<float, 3> velocity;
		// meters Collision and gravity epicenters
		gmtl::Vec<float, 3> centerOfMass;
		// Kg. used for momentum, collisions, 
		float mass;

		// Add Force as if it was directed through the center of mass
		void AddForce(gmtl::Vec<float, 3> forceVector);
	};
}



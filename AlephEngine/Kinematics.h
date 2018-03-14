#pragma once

#include <gmtl/Vec.h>
#include <gmtl/Quat.h>
#include <gmtl/VecOps.h>

#include "EngineTime.h"
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
		~Kinematics();
	private:
		//Newtons (kg m) / s^2 Used to calculate acceleration on the object
		gmtl::Vec<float, 3> force;

	public:
		Kinematics(Entity* entity);
		Kinematics(Entity* entity, gmtl::Vec<float, 3> vel, gmtl::Quat<float> AV, gmtl::Vec<float, 3> CofM, float M, gmtl::Vec<float, 3> F);
		
		// meters/second use like vector x, y, z
		// meters/second use like vector [index]
		gmtl::Vec<float, 3> velocity;
		// Rotational axis
		gmtl::Quat<float> rotationalAxis;
		// Relitive UP orthogonal to rotationalAxis
		gmtl::Vec<float, 3> UP;
		// meters Collision and gravity epicenters
		gmtl::Vec<float, 3> centerOfMass;
		// Kg. used for momentum, collisions, 
		// Kg. used for momentum, collisions,
		float mass;

		// Add Force as if it was directed through the center of mass
		void AddForce(gmtl::Vec<float, 3> forceVector);
	};
}

		void MoveStep(); // Moves the entity acording to its physics

		void AddForce(gmtl::Vec<float, 3> addedForce);
	};
}
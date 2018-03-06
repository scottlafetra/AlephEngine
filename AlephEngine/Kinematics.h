#pragma once

#include <gmtl/Vec.h>
#include "Component.h"

namespace AlephEngine
{
	class Kinematics : public Component
	{
	public:
		Kinematics(Entity* entity);
		Kinematics(Entity* entity, gmtl::Vec<float, 3> vel, gmtl::Vec<float, 3> rotAxis, gmtl::Vec<float, 3> CofM, float M, float AV);
		
		// meters/second use like vector [index]
		gmtl::Vec<float, 3> velocity;
		// Rotational axis
		gmtl::Vec<float, 3> rotationalAxis;
		// Relitive UP orthogonal to rotationalAxis
		gmtl::Vec<float, 3> UP;
		// meters Collision and gravity epicenters
		gmtl::Vec<float, 3> centerOfMass;
		// Kg. used for momentum, collisions,
		float mass;
		// angular velocity float
		float angularV;
		void MoveStep(); // Moves the enitity acording to its physics
	};
}
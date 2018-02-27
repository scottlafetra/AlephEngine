#pragma once

#include <gmtl/Vec.h>
#include "Component.h"

namespace AlephEngine
{
	class Kinematics : public Component
	{
	public:
		Kinematics(Entity* entity);
		
		// meters/second use like vector x, y, z
		gmtl::Vec<float, 3> velocity;
		// meters Collision and gravity epicenters
		gmtl::Vec<float, 3> centerOfMass;
		// Kg. used for momentum, collisions, 
		float mass;
		
		static void MoveStep(); // Moves the enitity acording to its physics
	};
}



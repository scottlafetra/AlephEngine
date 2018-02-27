#pragma once

#include "Component.h"
#include "Point3D.h"

namespace AlephEngine
{
	class Kinematics : public Component
	{
	public:
		Kinematics(Entity* entity);
		
		// meters/second use like vector x, y, z
		gmtl::vector<float, 3> velocity;
		// meters Collision and gravity epicenters
		gmtl::vector<float, 3> centerOfMass;
		// Kg. used for momentum, collisions, 
		float mass;
		
		static void MoveStep(); // Moves the enitity acording to its physics
	};
}



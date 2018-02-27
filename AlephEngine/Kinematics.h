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
		AlephEngine::Point3D velocity;
		// meters Collision and gravity epicenters
		AlephEngine::Point3D centerOfMass;
		// Kg. used for momentum, collisions, 
		double mass;
		
		static void MoveStep(); // Moves the enitity acording to its physics
	};
}



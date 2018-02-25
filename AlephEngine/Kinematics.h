#pragma once

#include "Component.h"

namespace AlephEngine
{
	class Kinematics : public Component
	{
	public:
		Kinematics(Entity* entity);
		
		static void MoveStep(); // Moves the enitity acording to its physics
	};
}



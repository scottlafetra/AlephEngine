#pragma once

#include "Kinematics.h"
#include <gmtl/VecOps.h>

namespace AlephEngine
{
	class Gravity : public Component{
	public:
		// m^3 / kg / s^2
		const float G = 6.67 * pow(10, -11);
		Kinematics* myKinematics;
		Transform* myTransform;
		Gravity(Entity* entity);
		void attract(Kinematics& yourKin);

	};
}


#pragma once

#include "Kinematics.h"
#include <gmtl/VecOps.h>

namespace AlephEngine
{
	class Gravity : public Component{
	public:
		// m^3 / kg / s^2
		static float G;
		static float maxImpulse;
		Kinematics* myKinematics;
		Transform* myTransform;
		Gravity(Entity* entity);
		void attract(Kinematics& yourKin);

	};
}


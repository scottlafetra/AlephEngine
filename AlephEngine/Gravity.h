#pragma once

#include <gmtl/VecOps.h>

#include "Kinematics.h"

namespace AlephEngine
{
	class Gravity {
	public:
		// m^3 / kg / s^2
		const float G = 6.67 * pow(10, -11);
		Kinematics* m_myKin;
		Gravity(Kinematics& myKin);
		void attract(Kinematics& yourKin);

	};
}


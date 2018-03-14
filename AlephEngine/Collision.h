#pragma once

#include "Component.h"
#include "Kinematics.h"

#include <gmtl/Vec.h>

class Collision : public Component
{
public:
	Collision(Kinematics* kin);

	// Total momentum velocity + angular
	void getMomentum();
	Kinematics* myKin;


private:
	float momentum;
};
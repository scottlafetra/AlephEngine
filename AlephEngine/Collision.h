#pragma once

#include "Component.h"

#include <gmtl/Vec.h>

class Collision : public Component
{
public:
	Collision(Entity* entity);

	// Total momentum velocity + angular
	void getMomentum();



private:
	float momentum;
};
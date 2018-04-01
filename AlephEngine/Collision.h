#pragma once

#include "Component.h"
#include "Kinematics.h"

#include <gmtl/Vec.h>

class Coll { // MetaData about a collision

};

class Collision : public Component
{
public:
	Collision(Kinematics* kin);

	// Total momentum velocity + angular
	void getMomentum();
	Kinematics* myKin;

	Coll* checkCollision(Collision other);

	bool checkXBounds(Collision other);
	bool checkYBounds(Collision other);
	bool checkZBounds(Collision other);

	gmtl::Vec<float, 2>* getXBounds();
	gmtl::Vec<float, 2>* getYBounds();
	gmtl::Vec<float, 2>* getZBounds();

	bool isTrigger = false; //set true if we wnt to keep track of collision but not actually use physics based collision

private:
	float momentum;
	gmtl::Vec<float, 3> BoundingBoxCenter; //centerpoint
	gmtl::Vec<float, 3> BoundingBoxDems; //x,y,z
};
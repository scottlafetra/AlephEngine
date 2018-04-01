#pragma once

#include "Component.h"
#include "Kinematics.h"

#include <gmtl/Vec.h>
#include <cmath>

class Collision;

class Coll { // MetaData about a collision
public:

	Coll(Collision* c1, Collision* c2, float x, float y, float z) {
		X_overlap = x;
		Y_overlap = y;
		Z_overlap = z;
	}

	Collision* col_1;
	Collision* col_2;

	float X_overlap;
	float Y_overlap;
	float Z_overlap;

	//should contain instantanious velocity and/or current + last seen positions
};

class Collision : public Component{
public:
	Collision(Entity* entity, Kinematics* kin);

	// Total momentum velocity + angular
	void getMomentum();
	Kinematics* myKin;

	void updateBounds(std::vector<gmtl::Vec<float, 3>> points);

	Coll* checkCollision(Collision other); // This is run by physics master

	float checkXOverlap(Collision other);
	float checkYOverlap(Collision other);
	float checkZOverlap(Collision other);

	gmtl::Vec<float, 2>* getXBounds();
	gmtl::Vec<float, 2>* getYBounds();
	gmtl::Vec<float, 2>* getZBounds();

	gmtl::Vec<float, 3> getBoundingBoxCenter() {
		return BoundingBoxCenter;
	}

	gmtl::Vec<float, 3> getBoundingBoxDems() {
		return BoundingBoxDems;
	}

	bool isTrigger = false; //set true if we wnt to keep track of collision but not actually use physics based collision

private:
	float momentum;
	gmtl::Vec<float, 3> BoundingBoxCenter; //centerpoint
	gmtl::Vec<float, 3> BoundingBoxDems; //x,y,z
};
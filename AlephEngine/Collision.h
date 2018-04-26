#pragma once

#include "Component.h"
#include "Kinematics.h"

#include <gmtl/Vec.h>
#include <cmath>

class Collider;

class Collision { // MetaData about a collision
public:

	Collision(Collider* c1, Collider* c2, float x, float y, float z) {
		X_overlap = x;
		Y_overlap = y;
		Z_overlap = z;
	}

	Collider* col_1;
	Collider* col_2;

	float X_overlap;
	float Y_overlap;
	float Z_overlap;

	//should contain instantanious velocity and/or current + last seen positions
};

class Collider : public Component,  UpdateCallback{
public:
	Collider(Entity* entity);
	void Update() override;

	// Total momentum velocity + angular
	void getMomentum();
	Kinematics* myKin;

	void SetMesh( const std::vector<float>& collisionMesh );
	void updateBounds();

	Collision* checkCollision (Collider& other); // This is run by physics master

	float checkXOverlap( Collider& other);
	float checkYOverlap( Collider& other);
	float checkZOverlap( Collider& other);

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
	Transform* myTransform;
	std::vector<float> collisionMesh;
	gmtl::Vec<float, 3> BoundingBoxCenter; //centerpoint
	gmtl::Vec<float, 3> BoundingBoxDems; //x,y,z
};
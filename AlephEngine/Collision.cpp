#include "Collision.h"

<<<<<<< HEAD
Collision::Collision(Entity* entity, Kinematics * kin) : Component(entity, Component::Type<Kinematics>()), myKin(kin){

}
=======
<<<<<<< HEAD
Collision::Collision(Entity* entity, Kinematics * kin) :
=======
>>>>>>> master
	Component(entity, Component::Type<Kinematics>()),
	myKin(kin)
{}
>>>>>>> parent of f60d1a0... Merged refactoring from master

void Collision::getMomentum(){

}

void Collision::updateBounds(std::vector<gmtl::Vec<float, 3>> points){
	float xMin = points[0][0];
	float xMax = points[0][0];
	float yMin = points[0][1];
	float yMax = points[0][1];
	float zMin = points[0][2];
	float zMax = points[0][2];
	
	for (int i = 1; i < points.size(); i++) {
		gmtl::Vec<float, 3> p = points[i];
<<<<<<< HEAD

void Collider::getMomentum(){

}

void Collider::updateBounds(std::vector<float> points){
	float xMin = points[0];
	float xMax = points[0];
	float yMin = points[1];
	float yMax = points[1];
	float zMin = points[2];
	float zMax = points[2];
	
	for (int i = 1; i < points.size(); i += 3) {
		gmtl::Vec<float, 3> p = gmtl::Vec<float, 3>(points[i], points[i + 1], points[i + 2]);

=======
=======
>>>>>>> master
>>>>>>> parent of f60d1a0... Merged refactoring from master
		if (p[0] > xMax) { xMax = p[0]; } else if (p[0] < xMin) xMin = p[0];
		if (p[1] > yMax) { yMax = p[1]; } else if (p[1] < yMin) yMin = p[1];
		if (p[2] > zMax) { zMax = p[2]; } else if (p[2] < zMin) zMin = p[2];
	}

	BoundingBoxDems = *new gmtl::Vec<float, 3>(std::abs(xMax - xMin), std::abs(yMax - yMin), std::abs(zMax - zMin));
	BoundingBoxCenter = *new gmtl::Vec<float, 3>(xMax - BoundingBoxDems[0] / 2, yMax - BoundingBoxDems[1] / 2, zMax - BoundingBoxDems[2] / 2);
}


Coll* Collision::checkCollision(Collision other){
<<<<<<< HEAD

Collision* Collider::checkCollision(Collider other){

=======
=======
>>>>>>> master
>>>>>>> parent of f60d1a0... Merged refactoring from master
	
	//if X overlaps
	float X_Overlap = checkXOverlap(other);
	if (X_Overlap > 0) {
		//if X overlaps
		float Y_Overlap = checkYOverlap(other);
		if (Y_Overlap > 0) {
			//if Z overlaps
			float Z_Overlap = checkZOverlap(other);
			if (Z_Overlap > 0) {
				//if we get here then the two objects have collided
				//TODO: return usefull info with Coll
				return new Coll(this, &other, X_Overlap, Y_Overlap, Z_Overlap);
<<<<<<< HEAD
				return new Collision(this, &other, X_Overlap, Y_Overlap, Z_Overlap);

=======
=======
>>>>>>> master
>>>>>>> parent of f60d1a0... Merged refactoring from master
			}
		}
	}
	//return nothing if we haven't collided
	return nullptr;
}

<<<<<<< HEAD
float Collision::checkXOverlap(Collision other){
=======
>>>>>>> master
	gmtl::Vec<float, 2> other_X = *other.getXBounds();
	gmtl::Vec<float, 2> this_X = *getXBounds();
	float overlap = 0;
	if (this_X[0] < other_X[0] && other_X[0] < this_X[1]) {
		//which ever is lower
		(this_X[1] - other_X[0]) > (other.getBoundingBoxDems()[0]) ? overlap = other.getBoundingBoxDems()[0] : overlap = this_X[1] - other_X[0];

	} else if (this_X[0] < other_X[1] && other_X[1] < this_X[1]) {
		overlap = other_X[1] - this_X[0];
	}

	return overlap;
}

<<<<<<< HEAD
float Collision::checkYOverlap(Collision other){
=======
>>>>>>> master
	gmtl::Vec<float, 2> other_Y = *other.getYBounds();
	gmtl::Vec<float, 2> this_Y = *getYBounds();
	float overlap = 0;
	if (this_Y[0] < other_Y[0] && other_Y[0] < this_Y[1]) {
		//which ever is lower
		(this_Y[1] - other_Y[0]) > (other.getBoundingBoxDems()[1]) ? overlap = other.getBoundingBoxDems()[1] : overlap = this_Y[1] - other_Y[0];

	}
	else if (this_Y[0] < other_Y[1] && other_Y[1] < this_Y[1]) {
		overlap = other_Y[1] - this_Y[0];
	}

	return overlap;
}

<<<<<<< HEAD
float Collision::checkZOverlap(Collision other){
=======
>>>>>>> master
	gmtl::Vec<float, 2> other_Z = *other.getZBounds();
	gmtl::Vec<float, 2> this_Z = *getZBounds();
	float overlap = 0;
	if (this_Z[0] < other_Z[0] && other_Z[0] < this_Z[1]) {
		//which ever is lower
		(this_Z[1] - other_Z[0]) > (other.getBoundingBoxDems()[2]) ? overlap = other.getBoundingBoxDems()[2] : overlap = this_Z[1] - other_Z[0];

	}
	else if (this_Z[0] < other_Z[1] && other_Z[1] < this_Z[1]) {
		overlap = other_Z[1] - this_Z[0];
	}

	return overlap;
}

<<<<<<< HEAD
gmtl::Vec<float, 2>* Collision::getXBounds(){
=======
>>>>>>> master
	float Lower = BoundingBoxCenter[0] - BoundingBoxDems[0] / 2;
	float Upper = BoundingBoxCenter[0] + BoundingBoxDems[0] / 2;
	return new gmtl::Vec<float, 2>(Lower, Upper);
}

<<<<<<< HEAD
gmtl::Vec<float, 2>* Collision::getYBounds(){
=======
>>>>>>> master
	float Lower = BoundingBoxCenter[1] - BoundingBoxDems[1] / 2;
	float Upper = BoundingBoxCenter[1] + BoundingBoxDems[1] / 2;
	return new gmtl::Vec<float, 2>(Lower, Upper);
}

<<<<<<< HEAD
gmtl::Vec<float, 2>* Collision::getZBounds(){
=======
>>>>>>> master
	float Lower = BoundingBoxCenter[2] - BoundingBoxDems[2] / 2;
	float Upper = BoundingBoxCenter[2] + BoundingBoxDems[2] / 2;
	return new gmtl::Vec<float, 2>(Lower, Upper);
}

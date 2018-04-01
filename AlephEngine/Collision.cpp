#include "Collision.h"

Collision::Collision(Kinematics * kin){

}

void Collision::getMomentum(){

}

Coll* Collision::checkCollision(Collision other){
	
	//if either of our points are between other's X bounds
	if (checkXBounds(other)) {
		//if either of our points are between other's Y bounds
		if (checkYBounds(other)) {
			//if either of our points are between other's Z bounds
			if (checkZBounds(other)) {
				//if we get here then the two objects have collided
				//TODO: return usefull info with Coll
				return new Coll();
			}
		}
	}
	//return nothing if we haven't collided
	return nullptr;
}

bool Collision::checkXBounds(Collision other){
	gmtl::Vec<float, 2> other_X = *other.getXBounds();
	gmtl::Vec<float, 2> this_X = *getXBounds();
	return (other_X[0] > this_X[0] && other_X[0] < this_X[1]) || (other_X[1] > this_X[0] && other_X[1] < this_X[1]);
}

bool Collision::checkYBounds(Collision other){
	gmtl::Vec<float, 2> other_Y = *other.getYBounds();
	gmtl::Vec<float, 2> this_Y = *getYBounds();
	return (other_Y[0] > this_Y[0] && other_Y[0] < this_Y[1]) || (other_Y[1] > this_Y[0] && other_Y[1] < this_Y[1]);
}

bool Collision::checkZBounds(Collision other){
	gmtl::Vec<float, 2> other_Z = *other.getZBounds();
	gmtl::Vec<float, 2> this_Z = *getZBounds();
	return (other_Z[0] > this_Z[0] && other_Z[0] < this_Z[1]) || (other_Z[1] > this_Z[0] && other_Z[1] < this_Z[1]);
}

gmtl::Vec<float, 2>* Collision::getXBounds(){
	float Lower = BoundingBoxCenter[0] - BoundingBoxDems[0] / 2;
	float Upper = BoundingBoxCenter[0] + BoundingBoxDems[0] / 2;
	return new gmtl::Vec<float, 2>(Lower, Upper);
}

gmtl::Vec<float, 2>* Collision::getYBounds(){
	float Lower = BoundingBoxCenter[1] - BoundingBoxDems[1] / 2;
	float Upper = BoundingBoxCenter[1] + BoundingBoxDems[1] / 2;
	return new gmtl::Vec<float, 2>(Lower, Upper);
}

gmtl::Vec<float, 2>* Collision::getZBounds(){
	float Lower = BoundingBoxCenter[2] - BoundingBoxDems[2] / 2;
	float Upper = BoundingBoxCenter[2] + BoundingBoxDems[2] / 2;
	return new gmtl::Vec<float, 2>(Lower, Upper);
}

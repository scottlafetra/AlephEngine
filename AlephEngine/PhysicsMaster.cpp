#include "PhysicsMaster.h"

#include "Collision.h"
#include "Kinematics.h"
#include "Transform.h"
#include "EngineTime.h"
#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>
#include <iterator> 

void PhysicsMaster::collideObjects(Coll c){
	//TODO actually do the collision
	//remember to check if dirty so we can break infinite loops
}

void PhysicsMaster::TrackPhysics(AlephEngine::Kinematics* toAdd){
	KinematicsList.push_back(toAdd);
}

void PhysicsMaster::StopTrackingPhysics(AlephEngine::Kinematics* toAdd){
	KinematicsList.remove(toAdd);
}

void PhysicsMaster::TrackCollision(Collision* toAdd){
	CollisionList.push_back(toAdd);
}

void PhysicsMaster::StopTrackingCollision(Collision* toAdd) {
	CollisionList.remove(toAdd);
}

void PhysicsMaster::StepPhysics(){
	for (AlephEngine::Kinematics* k : KinematicsList){
		gmtl::Vec<float, 3> accel = k->force;

		accel /= k->mass;

		k->velocity += accel * (float) EngineTime::GetDeltaTime();

		// Move step
		k->myTransform->Move(k->velocity * (float) EngineTime::GetDeltaTime());

		// Reset
		k->force = gmtl::Vec<float, 3>(0, 0, 0);
<<<<<<< HEAD
	}

	std::list<Collision*> updatedObjects;

	//loop through everything to see if things collide
	std::list<Collision*>::iterator i = CollisionList.begin();
	std::list<Collision*>::iterator j = CollisionList.begin();
	while ( i != CollisionList.end()) {//super ineffient way
		while (j != CollisionList.end()) {
			if ((*i) != (*j)) {//if it is not the same Collision
				Coll* c = (*i)->checkCollision(**j);
				if (c != nullptr) {//if there was a collision
					collideObjects(*c);
					updatedObjects.push_back((*i));
					updatedObjects.push_back((*j));
				}
			}
			j++;
		}
		j = CollisionList.begin();
		i++;
	}

	//second pass to loop through everything that collided to see if nudging them caused any further collisions
	while (updatedObjects.size > 0) {
		i = updatedObjects.begin();
		while (i != updatedObjects.end()) {//super ineffient way
			while (j != CollisionList.end()) {
				if ((*i) != (*j)) {//if it is not the same Collision
					Coll* c = (*i)->checkCollision(**j);
					if (c != nullptr) {//if there was a collision
						collideObjects(*c);
						updatedObjects.push_front((*j));
					} else {
						updatedObjects.remove((*i));
					}
				}
				j++;
			}
			j = CollisionList.begin();
			i++;
		}
=======
>>>>>>> master
	}
	
}

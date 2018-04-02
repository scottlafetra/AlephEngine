#pragma once
#include <list>

namespace AlephEngine
{
	// Forward Declaration
	class Kinematics;
	class Collision;
	class Coll;

	class PhysicsMaster
	{
	private:
		std::list<Kinematics*> KinematicsList;
		std::list<Collision*> CollisionList; //TODO: make this a tree

		void collideObjects(Coll c);

	public:

		void TrackPhysics(Kinematics* toAdd);
		void StopTrackingPhysics(Kinematics* toAdd);

		void TrackCollision(Collision* toAdd);
		void StopTrackingCollision(Collision* toAdd);

		void StepPhysics();


	};
}



#pragma once
#include <list>

namespace AlephEngine
{
	// Forward Declaration
	class Kinematics;

	class PhysicsMaster
	{
	private:
		std::list<Kinematics*> tracking;

	public:

		void TrackPhysics(Kinematics* toAdd);
		void StopTrackingPhysics(Kinematics* toAdd);

		void StepPhysics();
	};
}



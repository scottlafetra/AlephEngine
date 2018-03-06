#include "Kinematics.h"
#include "EngineTime.h"

AlephEngine::Kinematics::Kinematics(Entity * entity) :
	Component(entity, Component::Type<Kinematics>()),
	velocity(gmtl::Vec<float, 3>()),
	rotationalAxis(gmtl::Vec<float, 3>()),
	centerOfMass(gmtl::Vec<float, 3>()),
	mass(0.0),
	angularV(0.0)
{ }

AlephEngine::Kinematics::Kinematics(Entity * entity, gmtl::Vec<float, 3> vel, gmtl::Vec<float, 3> rotAxis, gmtl::Vec<float, 3> CofM, float M, float AV) :
	Component(entity, Component::Type<Kinematics>()),
	velocity(vel),
	rotationalAxis(rotAxis),
	centerOfMass(CofM),
	mass(M),
	angularV(AV)
{ }


void AlephEngine::Kinematics::MoveStep()
{
	// TODO: Fill in code here
	centerOfMass[0] += velocity[0] * EngineTime::GetDeltaTime();
	centerOfMass[1] += velocity[1] * EngineTime::GetDeltaTime();
	centerOfMass[2] += velocity[2] * EngineTime::GetDeltaTime();

}
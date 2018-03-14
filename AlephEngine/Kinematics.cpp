#include "Kinematics.h"

AlephEngine::Kinematics::Kinematics(Entity * entity) :
	Component(entity, Component::Type<Kinematics>()),
	velocity(gmtl::Vec<float, 3>()),
	rotationalAxis(gmtl::Quat<float>()),
	centerOfMass(gmtl::Vec<float, 3>()),
	mass(0.0),
	force(gmtl::Vec<float, 3>())
{ }

AlephEngine::Kinematics::Kinematics(Entity * entity, gmtl::Vec<float, 3> vel, gmtl::Quat<float> AV, gmtl::Vec<float, 3> CofM, float M, gmtl::Vec<float, 3> F) :
	Component(entity, Component::Type<Kinematics>()),
	velocity(vel),
	rotationalAxis(AV),
	centerOfMass(CofM),
	mass(M),
	force(F)
{ }


void AlephEngine::Kinematics::MoveStep()
{
	// TODO: Fill in code here
	//TODO: center of mass should change based on the objects updated position (done by )
	centerOfMass[0] += velocity[0]*EngineTime::GetDeltaTime();
	centerOfMass[1] += velocity[1] * EngineTime::GetDeltaTime();
	centerOfMass[2] += velocity[2] * EngineTime::GetDeltaTime();

	velocity += force / mass * (float) EngineTime::GetDeltaTime();

	force.set(0,0,0);
}

void AlephEngine::Kinematics::AddForce(gmtl::Vec<float, 3> addedForce)
{
	force += addedForce;
}

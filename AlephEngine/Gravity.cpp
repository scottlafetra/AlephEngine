#include "Gravity.h"

AlephEngine::Gravity::Gravity(Kinematics& myKin) :
	m_myKin(&myKin)
{ }

void AlephEngine::Gravity::attract(Kinematics & yourKin)
{
	//distanceComponents = m_myKin - yourKin
	gmtl::Vec<float, 3> direction = m_myKin->centerOfMass - yourKin.centerOfMass;
	
	//distance
	float distance = sqrt( pow(direction[0], 2 ) + pow(direction[1], 2 ) + pow(direction[2], 2 ) );
	// force kg*m/s/s
	float forceMagnitude = ( G * m_myKin->mass * yourKin.mass / pow(distance, 2 ) );

	gmtl::Vec<float, 3> newForce = direction / distance * forceMagnitude;

	m_myKin->AddForce(newForce);
        yourKin.AddForce(newForce * (float) -1);
}

#include "Gravity.h"

AlephEngine::Gravity::Gravity(Kinematics& myKin) :
	m_myKin(&myKin)
{ }

void AlephEngine::Gravity::attract(Kinematics & yourKin)
{
	//distanceComponents = m_myKin - yourKin
	std::vector<float> dcomps;
	for (int i = 0; i < m_myKin->centerOfMass.Size; i++) {
		dcomps.push_back(m_myKin->centerOfMass[i] - yourKin.centerOfMass[i]);
	}
	
	//distance
	float d = sqrt( pow( dcomps[0], 2 ) + pow( dcomps[1], 2 ) + pow( dcomps[2], 2 ) ); 
	// force kg*m/s/s
	float f = ( G * m_myKin->mass * yourKin.mass / pow( d, 2 ) ); 

	// vec of acc. for yourKin
	std::vector< float > accvec = { dcomps[0]*f / ( d*yourKin.mass ), dcomps[1]*f / (d*yourKin.mass), dcomps[2]*f / (d*yourKin.mass) }; 
	for (int i = 0; i < m_myKin->velocity.Size; i++) {
		yourKin.velocity[i] += accvec[i];
	}

	// vec of acc. for myKin
	accvec = std::vector<float>{-dcomps[0]*f / ( d*m_myKin->mass ), -dcomps[1]*f / (d*m_myKin->mass), -dcomps[2]*f / (d*m_myKin->mass) };
	for (int i = 0; i < m_myKin->velocity.Size; i++) {
		m_myKin->velocity[i] += accvec[i];
	}
}
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

<<<<<<< HEAD
	// vec of acc. for yourKin
	std::vector< float > accvec = { dcomps[0]*f / ( d*yourKin.mass ),
									dcomps[1]*f / ( d*yourKin.mass ),
									dcomps[2]*f / ( d*yourKin.mass ) }; 
=======
	// vec of meters^s / second for yourKin
	std::vector< float > Nmm_s = { dcomps[0]*f / ( d*yourKin.mass ), dcomps[1]*f / (d*yourKin.mass), dcomps[2]*f / (d*yourKin.mass) }; 
>>>>>>> Kinematics
	for (int i = 0; i < m_myKin->velocity.Size; i++) {
		yourKin.velocity[i] += Nmm_s[i];
	}

<<<<<<< HEAD
	// vec of acc. for myKin
	accvec = {	-dcomps[0]*f / ( d*m_myKin->mass ),
				-dcomps[1]*f / ( d*m_myKin->mass ),
				-dcomps[2]*f / ( d*m_myKin->mass ) };
=======
	// vec of Newton meters^s / second for myKin
	Nmm_s = std::vector<float>{-dcomps[0]*f / ( d*m_myKin->mass ), -dcomps[1]*f / (d*m_myKin->mass), -dcomps[2]*f / (d*m_myKin->mass) };
>>>>>>> Kinematics
	for (int i = 0; i < m_myKin->velocity.Size; i++) {
		m_myKin->velocity[i] += Nmm_s[i];
	}
}
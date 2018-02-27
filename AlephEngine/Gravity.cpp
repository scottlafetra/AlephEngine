#include "Gravity.h"

AlephEngine::Gravity::Gravity(Kinematics& myKin) :
	m_myKin(&myKin)
{ }

void AlephEngine::Gravity::attract(Kinematics & yourKin)
{
	//distanceComponents = m_myKin - yourKin
	std::vector<double> dcomps;
	dcomps.push_back(m_myKin->centerOfMass.x - yourKin.centerOfMass.x);
	dcomps.push_back(m_myKin->centerOfMass.y - yourKin.centerOfMass.y);
	dcomps.push_back(m_myKin->centerOfMass.z - yourKin.centerOfMass.z);
	
	//distance
	double d = sqrt( pow( dcomps[0], 2 ) + pow( dcomps[1], 2 ) + pow( dcomps[2], 2 ) ); 
	// force kg*m/s/s
	double f = ( G * m_myKin->mass * yourKin.mass / pow( d, 2 ) ); 

	// vec of acc. for yourKin
	std::vector< double > accvec = { dcomps[0]*f / ( d*yourKin.mass ), dcomps[1]*f / (d*yourKin.mass), dcomps[2]*f / (d*yourKin.mass) }; 
	yourKin.velocity.x += accvec[0];
	yourKin.velocity.y += accvec[1];
	yourKin.velocity.z += accvec[2];
	// vec of acc. for myKin
	accvec = std::vector<double>{-dcomps[0]*f / ( d*m_myKin->mass ), -dcomps[1]*f / (d*m_myKin->mass), -dcomps[2]*f / (d*m_myKin->mass) };
	m_myKin->velocity.x += accvec[0];
	m_myKin->velocity.y += accvec[1];
	m_myKin->velocity.z += accvec[2];
}
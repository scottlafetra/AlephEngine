#include "Transform.h"
#include <Generate.h>
#include <EulerAngle.h>
#include <QuatOps.h>
#include <VecOps.h>
using namespace AlephEngine;

Transform::Transform( Entity* entity )
	: Component( entity, Component::Type<Transform>() ), isUpdated( false ) { }

gmtl::Matrix<float, 4, 4> Transform::GetTransfromMatrix()
{
	if( !isUpdated )
	{
		transformMatrix = 
			gmtl::makeRot<gmtl::Matrix<float, 4, 4>>( rotation ) 
			* gmtl::makeTrans<gmtl::Matrix<float, 4, 4>>( position );

		isUpdated = true;
	}

	return transformMatrix;
}

void Transform::SetPosition( const gmtl::Vec<float, 3>& newPosition )
{
	position = newPosition;

	isUpdated = false;
}

void Transform::SetPosition( const float& x, const float& y, const float& z = 0.0 )
{
	position[0] = x;
	position[1] = y;
	position[2] = z;

	isUpdated = false;
}

void Transform::Move( const gmtl::Vec<float, 3>& dPosition )
{
	Move( dPosition[0], dPosition[1], dPosition[2] );

	isUpdated = false;
}

void Transform::Move( const float& dx, const float& dy, const float& dz = 0.0 )
{
	position[0] += dx;
	position[1] += dy;
	position[2] += dz;

	isUpdated = false;
}

void Transform::SetRotation( const gmtl::Quat<float>& newRotation )
{
	rotation = newRotation;

	isUpdated = false;
}

void Transform::SetRotation( const float& x, const float& y, const float& z = 0.0 )
{
	gmtl::setRot( rotation, gmtl::EulerAngle<float, gmtl::XYZ>( x, y, z ) );

	isUpdated = false;
}

void Transform::Rotate( const gmtl::Quat<float>& dRotation )
{
	rotation *= dRotation;

	isUpdated = false;
}
void Transform::Rotate( const float& dx, const float& dy, const float& dz = 0.0 )
{
	gmtl::Quat<float> dRotation;
	gmtl::setRot( dRotation, gmtl::EulerAngle<float, gmtl::XYZ>( dx, dy, dz ) );

	Rotate( dRotation );

	isUpdated = false;
}
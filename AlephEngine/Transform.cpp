#include "Transform.h"
#include <gmtl/Generate.h>
#include <gmtl/EulerAngle.h>
#include <gmtl/QuatOps.h>
#include <gmtl/VecOps.h>
using namespace AlephEngine;

/// <summary>
/// Transform ctor.
/// </summary>
/// <param name="entity"></param>
Transform::Transform( Entity* entity )
	: Component( entity, Component::Type<Transform>() ), scale( 1.f ), isUpdated( false ), parent( NULL ) { }

/// <summary>
/// Get the transformation in matrix form.
/// </summary>
/// <returns>The transformation matrix.</returns>
gmtl::Matrix<float, 4, 4> Transform::GetTransfromMatrix()
{
	if( !isUpdated )
	{
		transformMatrix = 

			gmtl::makeTrans<gmtl::Matrix<float, 4, 4>>( position ) *
			gmtl::makeRot<gmtl::Matrix<float, 4, 4>>( rotation ) *
			gmtl::makeScale<gmtl::Matrix<float, 4, 4>>( scale );

		isUpdated = true;
	}

	return transformMatrix;
}

/// <summary>
/// Set the scale for the attached entity.
/// </summary>
/// <param name="newScale">The new scale.</param>
void Transform::SetScale( float newScale )
{
	scale = newScale;
	isUpdated = false;
}

/// <summary>
/// Scale the attached entity.
/// </summary>
/// <param name="factor">The amount to scale by multiplicitivly.</param>
void Transform::Scale( float factor )
{
	scale *= factor;
	isUpdated = false;
}

/// <summary>
/// Set the position of the attached entity in local space.
/// </summary>
/// <param name="newPosition">The new position.</param>
void Transform::SetPosition( const gmtl::Vec<float, 3>& newPosition )
{
	position = newPosition;

	isUpdated = false;
}

/// <summary>
/// Set the position of the attached entity in local space.
/// </summary>
/// <param name="x">The new x position.</param>
/// <param name="y">The new y position.</param>
/// <param name="z">The new z position.</param>
void Transform::SetPosition( const float& x, const float& y, const float& z)
{
	position[0] = x;
	position[1] = y;
	position[2] = z;

	isUpdated = false;
}

/// <summary>
/// Move/translate the attached entity in local space.
/// </summary>
/// <param name="dPosition">The amount to move by.</param>
void Transform::Move( const gmtl::Vec<float, 3>& dPosition )
{
	Move( dPosition[0], dPosition[1], dPosition[2] );

	isUpdated = false;
}

/// <summary>
/// Move/translate the attached entity in local space.
/// </summary>
/// <param name="dx">The amount to move on the x axis.</param>
/// <param name="dy">The amount to move on the y axis.</param>
/// <param name="dz">The amount to move on the z axis.</param>
void Transform::Move( const float& dx, const float& dy, const float& dz)
{
	position[0] += dx;
	position[1] += dy;
	position[2] += dz;

	isUpdated = false;
}

/// <summary>
/// Set the rotation of the attached entity.
/// </summary>
/// <param name="newRotation">The new rotation, represented as a quaternion.</param>
void Transform::SetRotation( const gmtl::Quat<float>& newRotation )
{
	rotation = newRotation;

	isUpdated = false;
}

/// <summary>
/// Set the rotation of the attached entity.
/// </summary>
/// <param name="x">The rotation around the x axis.</param>
/// <param name="y">The rotation around the y axis.</param>
/// <param name="z">The rotation around the z axis.</param>
void Transform::SetRotation( const float& x, const float& y, const float& z)
{
	gmtl::setRot( rotation, gmtl::EulerAngle<float, gmtl::XYZ>( x, y, z ) );

	isUpdated = false;
}

/// <summary>
/// Rotate the attached entity.
/// </summary>
/// <param name="dRotation">Amount to rotate by, as a quaternion.</param>
void Transform::Rotate( const gmtl::Quat<float>& dRotation )
{
	rotation *= dRotation;

	isUpdated = false;
}

/// <summary>
/// Rotate the attached entity.
/// </summary>
/// <param name="dx">Amount to rotate around the x axis.</param>
/// <param name="dy">Amount to rotate around the y axis.</param>
/// <param name="dz">Amount to rotate around the z axis.</param>
void Transform::Rotate( const float& dx, const float& dy, const float& dz )
{
	gmtl::Quat<float> dRotation;
	gmtl::setRot( dRotation, gmtl::EulerAngle<float, gmtl::XYZ>( dx, dy, dz ) );

	Rotate( dRotation );

	isUpdated = false;
}

/// <summary>
/// Set another transform component as the parent.
/// </summary>
/// <param name="newParent">A pointer to the transform to parent to.</param>
void Transform::SetAsParent( Transform* newParent )
{

	if( parent != NULL )
	{
		parent->children.remove( this );
	}

	parent = newParent;
	newParent->children.push_back( this );
}

/// <summary>
/// Set another transform as a child to this transform.
/// </summary>
/// <param name="newChild">A pointer to the transform to make a child.</param>
void Transform::SetAsChild( Transform* newChild )
{
	children.push_back( newChild );

	if( newChild->parent != NULL )
	{
		newChild->parent->children.remove( newChild );
	}

	newChild->parent = this;
}
#include "Rotates.h"
#include "Transform.h"
#include "EngineTime.h"

/// <summary>
/// A component for applying a constant rotation to the entity over time.
/// </summary>
/// <param name="entity">The entity to attach to.</param>
Rotates::Rotates( Entity* entity )
	: Component( entity, Type<Rotates>() ), myTransform( entity->FetchComponent<Transform>() )
{
	xSpeed = ySpeed = zSpeed = 0;
	
	GetScene()->AddUpdateCallback( this );
}

/// <summary>
/// Called once per frame. Rotates the entity.
/// </summary>
void Rotates::Update()
{
	myTransform->Rotate( 
		xSpeed * EngineTime::GetDeltaTime(),
		ySpeed * EngineTime::GetDeltaTime(),
		zSpeed * EngineTime::GetDeltaTime() 
		);
}

/// <summary>
/// Set the rotation speed.
/// </summary>
/// <param name="xSpeed">Speed to rotate about the x axis.</param>
/// <param name="ySpeed">Speed to rotate about the y axis.</param>
/// <param name="zSpeed">Speed to rotate about the z axis.</param>
void Rotates::SetSpeed( float xSpeed, float ySpeed, float zSpeed )
{
	Rotates::xSpeed = xSpeed;
	Rotates::ySpeed = ySpeed;
	Rotates::zSpeed = zSpeed;
}

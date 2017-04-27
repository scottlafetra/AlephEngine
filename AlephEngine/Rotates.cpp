#include "Rotates.h"
#include "Transform.h"
#include "EngineTime.h"

Rotates::Rotates( Entity* entity )
	: Component( entity, Type<Rotates>() ), myTransform( entity->FetchComponent<Transform>() )
{
	xSpeed = ySpeed = zSpeed = 0;
	
	GetScene()->AddUpdateCallback( this );
}

void Rotates::Update()
{
	myTransform->Rotate( 
		xSpeed * EngineTime::GetDeltaTime(),
		ySpeed * EngineTime::GetDeltaTime(),
		zSpeed * EngineTime::GetDeltaTime() 
		);
}

void Rotates::SetSpeed( float xSpeed, float ySpeed, float zSpeed )
{
	Rotates::xSpeed = xSpeed;
	Rotates::ySpeed = ySpeed;
	Rotates::zSpeed = zSpeed;
}

#include "CatMotion.h"
#include "Transform.h"
#include "EngineTime.h"

CatMotion::CatMotion( Entity* entity )
	: Component( entity, Type<CatMotion>() ), myTransform( entity->FetchComponent<Transform>() )
{
	speed = limit = 0;

	GetScene()->AddUpdateCallback( this );
}

void CatMotion::Update()
{
	myTransform->Move( speed * EngineTime::GetDeltaTime(), 0 );

	if(myTransform->GetPosition()[ 0 ] > limit)
	{
		myTransform->SetPosition(
			-limit,
			myTransform->GetPosition()[ 1 ],
			myTransform->GetPosition()[ 2 ]
			);
	}
}

void CatMotion::SetSpeed( float xSpeed )
{
	speed = xSpeed;
}
void CatMotion::SetLimit( float xLimit )
{
	limit = xLimit;
}
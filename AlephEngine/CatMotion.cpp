#include "CatMotion.h"
#include "Transform.h"
#include "EngineTime.h"
#include "Kinematics.h"

CatMotion::CatMotion( Entity* entity )
	: Component( entity, Type<CatMotion>() ), myTransform( entity->FetchComponent<Transform>() )
{
	speed = xLimit = yLimit = 0;

	GetScene()->AddUpdateCallback( this );
}

void CatMotion::Update()
{
	entity->FetchComponent<Kinematics>()->velocity = gmtl::Vec<float, 3>{ speed, 0, 0 };

	if(myTransform->GetPosition()[0] > xLimit)
	{
		myTransform->SetPosition(
			-xLimit,
			myTransform->GetPosition()[ 1 ],
			myTransform->GetPosition()[ 2 ]
			);
	}

	if (myTransform->GetPosition()[0] < -xLimit)
	{
		myTransform->SetPosition(
			xLimit,
			myTransform->GetPosition()[1],
			myTransform->GetPosition()[2]
		);
	}

	if (myTransform->GetPosition()[1] > yLimit)
	{
		myTransform->SetPosition(
			myTransform->GetPosition()[0],
			-yLimit,
			myTransform->GetPosition()[2]
		);
	}

	if (myTransform->GetPosition()[1] < -yLimit)
	{
		myTransform->SetPosition(
			myTransform->GetPosition()[0],
			yLimit,
			myTransform->GetPosition()[2]
		);
	}

}

void CatMotion::SetSpeed( float xSpeed )
{
	speed = xSpeed;
}

void CatMotion::SetLimit( float xLimit, float yLimit )
{
	CatMotion::xLimit = xLimit;
	CatMotion::yLimit = yLimit;
}
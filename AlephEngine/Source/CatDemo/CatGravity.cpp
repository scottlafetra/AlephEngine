#include "CatGravity.h"

std::list<Kinematics*> CatGravity::allCats = std::list<Kinematics*>();

CatGravity::CatGravity(Entity* entity)
	:Component(entity, Type<CatGravity>())
{
	if ((myGravity = entity->FetchComponent<Gravity>()) == NULL)
	{
		FatalError("CatGravity component not attached to entity with Gravity component.");
	}

	Kinematics* myKinematics;
	if ((myKinematics = entity->FetchComponent<Kinematics>()) == NULL)
	{
		FatalError("CatGravity component not attached to entity with Kinematics component.");
	}
	else
	{
		allCats.push_back(myKinematics);
	}

	GetScene()->AddUpdateCallback(this);
}
void CatGravity::Update()
{
	for (Kinematics* targetCat : allCats)
	{
		myGravity->attract(*targetCat);
	}
}
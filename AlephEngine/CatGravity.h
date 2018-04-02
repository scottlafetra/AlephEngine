#pragma once
#include <list>
#include "Component.h"
#include "Gravity.h"

class CatGravity : public Component, UpdateCallback
{
public:
	CatGravity(Entity* entity);
	void Update() override;

private:
	static std::list<Kinematics*> allCats;
	Gravity* myGravity;
};


#pragma once
#include <list>
#include "../Core/Component.h"
#include "../Physics/Gravity.h"

class CatGravity : public Component, UpdateCallback
{
public:
	CatGravity(Entity* entity);
	void Update() override;

private:
	static std::list<Kinematics*> allCats;
	Gravity* myGravity;
};


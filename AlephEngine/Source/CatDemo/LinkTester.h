#pragma once
#include "../Core/Component.h"


class LinkTester : public Component, UpdateCallback
{
public:
	LinkTester( Entity* entity );

	int secretNum;
	LinkTester * link;
	void Update() override;
};


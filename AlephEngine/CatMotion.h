#pragma once
#include "Component.h"

class CatMotion : public Component, UpdateCallback
{
private:
	Transform* myTransform;
	float xLimit, yLimit;
	float speed;

public:
	CatMotion( Entity* entity );
	void Update() override;

	void SetSpeed( float xSpeed );
	void SetLimit( float xLimit, float yLimit );

};

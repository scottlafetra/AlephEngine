#pragma once
#include "Component.h"

class Rotates : public Component, public UpdateCallback
{
private:
	float xSpeed, ySpeed, zSpeed;
	Transform* myTransform;

public:
	Rotates( Entity* entity );
	void Update() override;

	void SetSpeed( float xSpeed, float ySpeed, float zSpeed );

	inline float GetXSpeed() { return xSpeed; }
	inline float GetYSpeed() { return ySpeed; }
	inline float GetZSpeed() { return zSpeed; }
};
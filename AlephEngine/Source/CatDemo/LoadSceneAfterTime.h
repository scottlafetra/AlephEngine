#pragma once

#include "../Core/Component.h"

class LoadSceneAfterTime : public Component, UpdateCallback
{
	

	void Update() override;

public:
	LoadSceneAfterTime( Entity* entity );
	~LoadSceneAfterTime();

	std::string sceneToLoad;
	float timeToWait;
};
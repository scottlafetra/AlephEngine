#pragma once
#include <cstdlib>
#include "Scene.h"

int main(int argn, char* argc[])
{
	// Create the scene
	AlephEngine::Scene scene;

	

	// Run the scene
	scene.CreateAlephWindow( 800, 600 );
	scene.Play();

	//Scene is deleted on end
	return EXIT_SUCCESS;
}
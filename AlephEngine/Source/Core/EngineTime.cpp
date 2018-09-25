#include "EngineTime.h"
#include <GLFW\glfw3.h>

using namespace AlephEngine;

double EngineTime::time = 0;
double EngineTime::deltaTime = 0;

/// <summary>
/// Update the time variables that are avalible for use in engine.
/// </summary>
void EngineTime::UpdateTimes()
{
	double newTime = glfwGetTime();

	deltaTime = newTime - time;
	time = newTime;
}
#include "EngineTime.h"
#include <GLFW\glfw3.h>

using namespace AlephEngine;

double EngineTime::time = 0;
double EngineTime::deltaTime = 0;

void EngineTime::UpdateTimes()
{
	double newTime = glfwGetTime();

	deltaTime = newTime - time;
	time = newTime;
}
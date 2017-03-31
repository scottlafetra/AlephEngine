#pragma once
#include <GLFW/glfw3.h>
#include "lodepng.h"
#include <iostream>
#include <string>
using namespace std;

namespace AlephEngine
{
	class Utility
	{
	public:
		static GLFWimage* LoadGLFWImage( const string& filename );
	};
}
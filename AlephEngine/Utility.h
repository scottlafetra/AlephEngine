#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "lodepng.h"
#include <iostream>
#include <string>

namespace AlephEngine
{
	class Utility
	{
	public:
		static GLFWimage* LoadGLFWImage( const std::string& filename );
	};
}
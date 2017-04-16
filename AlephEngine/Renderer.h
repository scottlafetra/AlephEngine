#pragma once
#include <Matrix.h>
#include "Component.h"


namespace AlephEngine
{
	class Renderer : public Component
	{
	public:
		Renderer( Entity* entity );
		virtual void RenderOn( GLFWwindow* window, gmtl::Matrix<float, 4, 4> view );
	};
}
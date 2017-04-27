#pragma once
#include <gmtl/Matrix.h>
#include "Component.h"


namespace AlephEngine
{
	class Renderer : public Component
	{
	public:
		Renderer( Entity* entity );
		virtual void Render( gmtl::Matrix<float, 4, 4> view ) = NULL;
		GLuint shaderProgram;
	};
}
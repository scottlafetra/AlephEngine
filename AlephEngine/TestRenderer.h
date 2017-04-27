#pragma once
#include <GL/glew.h>
#include "Renderer.h"

class TestRenderer : public AlephEngine::Renderer
{
public:
	TestRenderer( AlephEngine::Entity* entity );
	void Render( gmtl::Matrix<float, 4, 4> view ) override;
};
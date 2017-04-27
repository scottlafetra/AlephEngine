#pragma once

#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/Generate.h>
#include "Component.h"
#include "Transform.h"

namespace AlephEngine
{
	class Camera : public Component, RenderCallback
	{
	private:
		GLFWwindow* renderWindow;
		int width, height;

		// Render settings
		bool orthographic;
		int viewWidth, viewHeight; // For ortho
		float fov;                 // For perspective 
		float nearLimit, farLimit; // Shared 

		gmtl::Matrix<float, 4, 4> projection;
		static void RenderSubnodes( Transform* root, gmtl::Matrix<float, 4, 4> mvp );

	public:
		void SetOrtho( int viewWidth, int viewHeight, float nearLimit, float farLimit );
		void SetPerspective( float fov, float nearLimit, float farLimit );

		Camera( Entity* entity, GLFWwindow* renderWindow );
		Camera( Entity* entity );

		void HandleResize();
		void Render() override;
	};
}

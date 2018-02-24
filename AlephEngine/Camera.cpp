#include "Camera.h"
#include "Component.h"
#include "Renderer.h"
using namespace AlephEngine;

/// <summary>
/// Camera ctor.
/// </summary>
/// <param name="entity">The entity to add this component to.</param>
/// <param name="renderWindow">The window to render to.</param>
Camera::Camera( Entity* entity, GLFWwindow* renderWindow )
	: Component( entity, Component::Type<Camera>() ), renderWindow( renderWindow ), orthographic( orthographic )
{
	SetOrtho( 1, 1, -1, 1 ); // Default view

	GetScene()->AddRenderCallback( this );
}

/// <summary>
/// Camera ctor.
/// </summary>
/// <param name="entity">The entity to add this component to.</param>
Camera::Camera( Entity* entity )
	: Component( entity, Component::Type<Camera>() ), orthographic( orthographic )
{
	renderWindow = GetScene()->GetWindows()[ 0 ];

	SetOrtho( 1, 1, -1, 1 ); // Default view

	GetScene()->AddRenderCallback( this );
}

/// <summary>
/// Handles the resizing of the window.
/// </summary>
void Camera::HandleResize()
{
	glfwGetFramebufferSize( renderWindow, &width, &height );

	glViewport( 0, 0, width, height );
	glClear( GL_COLOR_BUFFER_BIT );
	float aspectRatio = width / (float) height;

	if(orthographic)
	{
		gmtl::setOrtho( projection, -viewWidth / 2.f, -viewHeight / 2.f, viewWidth / 2.f, viewHeight / 2.f, nearLimit, farLimit );
	}
	else
	{
		gmtl::setPerspective( projection, fov, aspectRatio, nearLimit, farLimit );
	}

}

/// <summary>
/// Recursivly renders all transforms childed to the given transform.
/// </summary>
/// <param name="root">The transform to start at.</param>
/// <param name="mvp">The model view matrix to use in rendering.</param>
void Camera::RenderSubnodes( Transform* root, gmtl::Matrix<float, 4, 4> mvp )
{
	//cout << "Traversing through: " << root->GetEntity()->GetName() << endl;
	mvp = mvp * root->GetTransfromMatrix();

	Entity* entity = root->GetEntity();
	if(entity->renderable && entity->renderMe)
	{
		entity->FetchComponent<Renderer>()->Render( mvp );
	}

	// Render children
	std::list<Transform*> children = root->GetChildren();
	for(Transform* child : children)
	{
		RenderSubnodes( child, mvp );
	}
}

/// <summary>
/// Render the camera to the window.
/// </summary>
void Camera::Render()
{
	gmtl::Matrix<float, 4, 4> mvp = projection;

	// Taverse to the top and get transforms along the way
	Transform* focus = entity->FetchComponent<Transform>();
	for(; focus->GetParent() != NULL; focus = focus->GetParent())
	{
		mvp *= makeInvert( focus->GetTransfromMatrix() );
	}

	// Traverse down the tree (skips root)
	for(Transform* child : focus->GetChildren())
	{
		RenderSubnodes( child, mvp );
	}
}

/// <summary>
/// Set drawing to orthographic and set draw OpenGL thru gmtl.
/// </summary>
/// <param name="viewWidth">Width of the view.</param>
/// <param name="viewHeight">Height of the view.</param>
/// <param name="nearLimit">The closest objects should be drawn.</param>
/// <param name="farLimit">The farthest that objects should be drawn.</param>
void Camera::SetOrtho( int viewWidth, int viewHeight, float nearLimit, float farLimit )
{
	orthographic = true;
	Camera::viewWidth  = viewWidth;
	Camera::viewHeight = viewHeight;
	Camera::nearLimit  = nearLimit;
	Camera::farLimit   = farLimit;

	HandleResize();
}

/// <summary>
/// Set drawing to perspective and set draw settings OpenGL thru gmtl.
/// </summary>
/// <param name="fov">The field of view.</param>
/// <param name="nearLimit">The closest objects should be drawn.</param>
/// <param name="farLimit">The farthest that objects should be drawn.</param>
void Camera::SetPerspective( float fov, float nearLimit, float farLimit )
{
	orthographic = false;
	Camera::fov = fov;
	Camera::nearLimit = std::max( nearLimit, 0.0001f ); // Perspective limits cannot be 0 or below
	Camera::farLimit  = std::max(  farLimit, 0.0001f );

	HandleResize();
}
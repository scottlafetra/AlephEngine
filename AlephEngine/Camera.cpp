#include "Camera.h"
#include "Component.h"
#include "Renderer.h"
using namespace AlephEngine;

Camera::Camera( Entity* entity, GLFWwindow* renderWindow )
	: Component( entity, Component::Type<Camera>() ), renderWindow( renderWindow ), orthographic( orthographic )
{
	SetOrtho( 1, 1, -1, 1 ); // Default view

	GetScene()->AddRenderCallback( this );
}

Camera::Camera( Entity* entity )
	: Component( entity, Component::Type<Camera>() ), orthographic( orthographic )
{
	renderWindow = GetScene()->GetWindows()[ 0 ];

	SetOrtho( 1, 1, -1, 1 ); // Default view

	GetScene()->AddRenderCallback( this );
}

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
	list<Transform*> children = root->GetChildren();
	for(Transform* child : children)
	{
		RenderSubnodes( child, mvp );
	}
}

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

void Camera::SetOrtho( int viewWidth, int viewHeight, float nearLimit, float farLimit )
{
	orthographic = true;
	Camera::viewWidth  = viewWidth;
	Camera::viewHeight = viewHeight;
	Camera::nearLimit  = nearLimit;
	Camera::farLimit   = farLimit;

	HandleResize();
}

void Camera::SetPerspective( float fov, float nearLimit, float farLimit )
{
	orthographic = false;
	Camera::fov = fov;
	Camera::nearLimit = max( nearLimit, 0.0001f ); // Perspective limits cannot be 0 or below
	Camera::farLimit  = max(  farLimit, 0.0001f );

	HandleResize();
}
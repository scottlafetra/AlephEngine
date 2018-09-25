#include "Renderer.h"

/// <summary>
/// Renderer ctor.
/// </summary>
/// <param name="entity">The entity this renderer should be attached to.</param>
Renderer::Renderer( Entity* entity )
	: Component( entity, Type<Renderer>() ), shaderProgram( NULL ) // All children count as a renderer
{ 
	entity->renderMe = true;
	entity->renderable = true;
}
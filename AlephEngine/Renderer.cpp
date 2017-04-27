#include "Renderer.h"

Renderer::Renderer( Entity* entity )
	: Component( entity, Type<Renderer>() ), shaderProgram( NULL ) // All children count as a renderer
{ 
	entity->renderMe = true;
	entity->renderable = true;
}
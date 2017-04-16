#include "Renderer.h"

Renderer::Renderer( Entity* entity )
	: Component( entity, Type<Renderer>() ) // All children count as a renderer
{ 
	entity->renderMe = true;
}
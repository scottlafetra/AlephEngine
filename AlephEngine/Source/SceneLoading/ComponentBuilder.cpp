#include "ComponentBuilder.h"
#include "Builders\All.h"

IBuilder* AlephEngine::CreateComponentBuilder( Entity* entity, std::string className )
{
	if( className == "Camera" )
	{
		return new CameraBuilder( entity );
	}
	else if( className == "MeshRenderer<StdUnlit>" )
	{
		return new BasicMeshRedererBuilder( entity );
	}
	else
	{
		std::cerr << "Error: Classname \"" + className + "\" not found." << std::endl;
		return nullptr;
	}
}
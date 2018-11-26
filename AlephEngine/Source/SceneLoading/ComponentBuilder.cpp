#include "ComponentBuilder.h"
#include "Builders\All.h"

std::unordered_map<std::string, Component*> IBuilder::componentIDs = std::unordered_map<std::string, Component*>();
std::vector<std::pair<std::string, Component**>> IBuilder::componentLinks = std::vector<std::pair<std::string, Component**>>();

IBuilder* AlephEngine::CreateComponentBuilder( Entity* entity, std::string className )
{
	if( className == "Camera" )
	{
		return new CameraBuilder( entity );
	}
	else if( className == "MeshRenderer<StdUnlit>" )
	{
		return new BasicMeshRendererBuilder( entity );
	}
	else if( className == "MeshRenderer<UnlitTexture>" )
	{
		return new BasicTextureMeshRendererBuilder( entity );
	}
	else if( className == "LinkTester" )
	{
		return new LinkTesterBuilder( entity );
	}
	else if( className == "LoadSceneAfterTime" )
	{
		return new LoadSceneAfterTimeBuilder( entity );
	}
	else
	{
		std::cerr << "Error: Classname \"" + className + "\" not found." << std::endl;
		return nullptr;
	}
}

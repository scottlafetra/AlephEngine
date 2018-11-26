#include "LoadSceneAfterTimeBuilder.h"

LoadSceneAfterTimeBuilder::LoadSceneAfterTimeBuilder( Entity* entity )
{
	producing = entity->AddComponent<LoadSceneAfterTime>();
}

void LoadSceneAfterTimeBuilder::AddVar( std::string name, std::string value )
{
	if( name == "sceneToLoad" )
	{
		producing->sceneToLoad = value;
	}
	else if( name == "timeToWait" )
	{
		producing->timeToWait = std::stof( value );
	}
	else
	{
		std::cerr << "ERROR: No variable named \"" + name + "\" in the LoadSceneAfterTime component." << std::endl;
	}
}

void LoadSceneAfterTimeBuilder::SetID( std::string id )
{
	componentIDs.emplace( id, producing );
}
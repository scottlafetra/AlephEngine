#include "LinkTesterBuilder.h"

LinkTesterBuilder::LinkTesterBuilder( Entity* entity )
{
	producing = entity->AddComponent<LinkTester>();
}

void LinkTesterBuilder::AddVar( std::string name, std::string value )
{
	if( name == "link" )
	{
		componentLinks.push_back( std::pair<std::string, Component**>( value, (Component**) &producing->link ) );
	}
	else if( name == "secretNum" )
	{
		producing->secretNum = std::stoi( value );
	}
	else
	{
		std::cerr << "ERROR: No variable named \"" + name + "\" in the LinkTester component." << std::endl;
	}
}

void LinkTesterBuilder::SetID( std::string id )
{
	componentIDs.emplace( id, producing );
}
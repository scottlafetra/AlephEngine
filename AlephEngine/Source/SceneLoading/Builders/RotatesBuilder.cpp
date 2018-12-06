#include "RotatesBuilder.h"

AlephEngine::RotatesBuilder::RotatesBuilder( Entity * entity )
: xSpeed(0), ySpeed(0), zSpeed(0)
{
	producing = entity->AddComponent<Rotates>();
}

void AlephEngine::RotatesBuilder::AddVar( std::string name, std::string value )
{
	if( name == "xSpeed" )
	{
		xSpeed = std::stof( value );
	}
	else if( name == "ySpeed" )
	{
		ySpeed = std::stof( value );
	}
	else if( name == "zSpeed" )
	{
		zSpeed = std::stof( value );
	}
	else
	{
		std::cerr << "ERROR: No variable named \"" + name + "\" in the Camera component." << std::endl;
		return;
	}

	// If we didn't return from error, update stuff
	producing->SetSpeed( xSpeed, ySpeed, zSpeed );
}

void AlephEngine::RotatesBuilder::SetID( std::string id )
{
	componentIDs.emplace( id, producing );
}

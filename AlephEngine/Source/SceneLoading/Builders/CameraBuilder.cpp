#pragma once
#include "CameraBuilder.h"

#include "../../Rendering/Camera.h"
#include "../../Core/Entity.h"
#include <iostream>
#include <algorithm>

CameraBuilder::CameraBuilder( Entity* entity )
{
	producing = entity->AddComponent<Camera>();
}

// TODO: add ortho support
void CameraBuilder::AddVar( std::string name, std::string value )
{
	if( name == "fov" )
	{
		producing->SetPerspective( std::stof( value ), producing->nearLimit, producing->farLimit );
	}
	else if( name == "nearLimit" )
	{
		float newNearLimit = std::stof( value );
		producing->SetPerspective( producing->fov, newNearLimit, std::max( producing->farLimit, newNearLimit + 0.001f) );
	}
	else if( name == "farLimit" )
	{
		float newFarLimit = std::stof( value );
		producing->SetPerspective( producing->fov, std::min( newFarLimit - 0.001f, producing->nearLimit ), newFarLimit );
	}
	else
	{
		std::cerr << "ERROR: No variable named \"" + name + "\" in the Camera component." << std::endl;
	}
}
#pragma once
#include "../../CatDemo/Testing.h"

#include "BasicMeshRendererBuilder.h"
#include "../../Rendering/MeshRenderer.h"


BasicMeshRendererBuilder::BasicMeshRendererBuilder( Entity* entity )
{
	producing = entity->AddComponent<MeshRenderer<Shaders::StdUnlit>>();
	
}

// TODO: add ortho support
void BasicMeshRendererBuilder::AddVar( std::string name, std::string value )
{
	if( name == "mesh" )
	{
		if( value == "cube" )
		{
			((MeshRenderer<Shaders::StdUnlit>*) producing)->SetVertices( GL_TRIANGLES, 3 * 2 * 6, (GLfloat*)testCube );
		}
		else if( value == "quad" )
		{
			((MeshRenderer<Shaders::StdUnlit>*) producing)->SetVertices( GL_TRIANGLES, 6, (GLfloat*)testQuad );
		}
		else if( value == "tri" )
		{
			((MeshRenderer<Shaders::StdUnlit>*) producing)->SetVertices( GL_TRIANGLES, 3, (GLfloat*)testTri );
		}
		else
		{
			std::cerr << "ERROR: No mesh named \"" + value + "\" in the MeshRenderer<Shaders::StdUnlit> component." << std::endl;
		}
	}
	else
	{
		std::cerr << "ERROR: No variable named \"" + name + "\" in the MeshRenderer<Shaders::StdUnlit> component." << std::endl;
	}
}

void BasicMeshRendererBuilder::SetID( std::string id )
{
	componentIDs.emplace( id, producing );
}
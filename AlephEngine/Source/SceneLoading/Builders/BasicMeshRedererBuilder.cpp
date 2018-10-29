#pragma once
#include "../../CatDemo/Testing.h"

#include "BasicMeshRedererBuilder.h"
#include "../../Rendering/MeshRenderer.h"


BasicMeshRedererBuilder::BasicMeshRedererBuilder( Entity* entity )
{
	producing = entity->AddComponent<MeshRenderer<Shaders::StdUnlit>>();
	((MeshRenderer<Shaders::StdUnlit>*) producing)->SetVertices( GL_TRIANGLES, 3 * 2 * 6, (GLfloat*)testCube );
}

// TODO: add ortho support
void BasicMeshRedererBuilder::AddVar( std::string name, std::string value )
{
	std::cerr << "ERROR: No variable named \"" + name + "\" in the MeshRenderer<Shaders::StdUnlit> component." << std::endl;
}
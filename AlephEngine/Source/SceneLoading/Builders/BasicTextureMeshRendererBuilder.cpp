#include "BasicTextureMeshRendererBuilder.h"
#include "../../CatDemo/Testing.h"

AlephEngine::BasicTextureMeshRendererBuilder::BasicTextureMeshRendererBuilder( Entity * entity )
{
	producing = entity->AddComponent<MeshRenderer<Shaders::UnlitTexture>>();
}

void AlephEngine::BasicTextureMeshRendererBuilder::AddVar( std::string name, std::string value )
{
	if( name == "texture" )
	{
		producing->SetTexture( Utility::LoadGLFWImage( value ), GL_CLAMP_TO_BORDER );
	}
	if( name == "mesh" )
	{
		if( value == "cube" )
		{
			producing->SetVertices( GL_TRIANGLES, 3 * 2 * 6, (GLfloat*)catCube );
		}
		else if( value == "quad" )
		{
			producing->SetVertices( GL_TRIANGLES, 3 * 2 * 6, (GLfloat*)texQuad );
		}
		else
		{
			std::cerr << "ERROR: No mesh named \"" + value + "\" in the MeshRenderer<Shaders::UnlitTexture> component." << std::endl;
		}
	}
	else
	{
		std::cerr << "ERROR: No variable named \"" + name + "\" in the Camera component." << std::endl;
	}
}

void AlephEngine::BasicTextureMeshRendererBuilder::SetID( std::string id )
{
	componentIDs.emplace( id, producing );
}

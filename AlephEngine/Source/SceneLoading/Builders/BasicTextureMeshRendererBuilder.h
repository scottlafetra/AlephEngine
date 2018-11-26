#pragma once
#include "../ComponentBuilder.h"
#include "../../Rendering/MeshRenderer.h"

namespace AlephEngine
{
	class BasicTextureMeshRendererBuilder : public IBuilder
	{
	public:
		BasicTextureMeshRendererBuilder( Entity* entity );
		void AddVar( std::string name, std::string value ) override;
		void SetID( std::string id ) override;

	private:
		MeshRenderer<Shaders::UnlitTexture> * producing;
	};
}
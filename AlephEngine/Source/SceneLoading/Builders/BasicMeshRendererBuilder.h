#pragma once


#include "../ComponentBuilder.h"
#include "../../Core/Entity.h"



namespace AlephEngine
{

	class BasicMeshRendererBuilder : public IBuilder
	{
	public:
		BasicMeshRendererBuilder( Entity* entity );
		void AddVar( std::string name, std::string value ) override;
		void SetID( std::string id ) override;

	private:
		Renderer * producing;
	};
}



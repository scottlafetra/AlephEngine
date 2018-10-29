#pragma once


#include "../ComponentBuilder.h"
#include "../../Core/Entity.h"



namespace AlephEngine
{

	class BasicMeshRedererBuilder : public IBuilder
	{
	public:
		BasicMeshRedererBuilder( Entity* entity );
		void AddVar( std::string name, std::string value ) override;

	private:
		Renderer * producing;
	};
}



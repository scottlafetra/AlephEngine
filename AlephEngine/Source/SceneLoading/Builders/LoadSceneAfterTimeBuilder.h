#pragma once
#include "../ComponentBuilder.h"
#include "../../Core/Entity.h"

#include "../../CatDemo/LoadSceneAfterTime.h"

namespace AlephEngine
{

	class LoadSceneAfterTimeBuilder : public IBuilder
	{
	public:
		LoadSceneAfterTimeBuilder( Entity* entity );
		void AddVar( std::string name, std::string value ) override;
		void SetID( std::string id ) override;

	private:
		LoadSceneAfterTime * producing;
	};
}
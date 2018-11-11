#pragma once
#include "../ComponentBuilder.h"
#include "../../Core/Entity.h"

#include "../../CatDemo/LinkTester.h"

namespace AlephEngine
{

	class LinkTesterBuilder : public IBuilder
	{
	public:
		LinkTesterBuilder( Entity* entity );
		void AddVar( std::string name, std::string value ) override;
		void SetID( std::string id ) override;

	private:
		LinkTester * producing;
	};
}
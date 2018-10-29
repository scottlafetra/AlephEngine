#pragma once

#include <string>
#include "../Core/Entity.h"
#include "../Core/Component.h"

namespace AlephEngine
{
	class IBuilder {
	public:
		virtual void AddVar( std::string name, std::string value ) = 0;
	};

	IBuilder* CreateComponentBuilder( Entity* entity, std::string className );
}
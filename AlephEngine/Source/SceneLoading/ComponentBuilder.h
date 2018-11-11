#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include "../Core/Entity.h"
#include "../Core/Component.h"

namespace AlephEngine
{
	class IBuilder {
	public:
		static std::unordered_map<std::string, Component*> componentIDs;
		static std::vector<std::pair<std::string, Component**>> componentLinks;

		virtual void AddVar( std::string name, std::string value ) = 0;
		virtual void SetID( std::string id ) = 0;
	};

	IBuilder* CreateComponentBuilder( Entity* entity, std::string className );

}
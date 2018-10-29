#pragma once

#include "../ComponentBuilder.h"
#include "../../Rendering/Camera.h"

namespace AlephEngine
{
	class CameraBuilder : public IBuilder
	{
	public:
		CameraBuilder( Entity* entity );
		void AddVar( std::string name, std::string value ) override;

	private:
		Camera * producing;
	};
}
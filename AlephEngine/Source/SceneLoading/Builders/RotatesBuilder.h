#pragma once
#include "../ComponentBuilder.h"
#include "../../Rotates.h"

namespace AlephEngine
{
	class RotatesBuilder : public IBuilder
	{
	public:
		RotatesBuilder( Entity* entity );
		void AddVar( std::string name, std::string value ) override;
		void SetID( std::string id ) override;

	private:
		Rotates * producing;

		float xSpeed;
		float ySpeed;
		float zSpeed;
	};
}

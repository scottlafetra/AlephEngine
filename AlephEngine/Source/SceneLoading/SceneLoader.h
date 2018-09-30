#pragma once

#include <string>
#include "../Core/Scene.h"

namespace AlephEngine 
{
	static class SceneLoader
	{
	public:
		/// <summary>
		/// Loads a .aleph file and constructs the scene saved in it.
		/// </summary>
		/// <param name="path"> The path to the scene file. </param>
		/// <returns> The constructed scene. </returns>
		static Scene* LoadScene( std::string path );
	};
}



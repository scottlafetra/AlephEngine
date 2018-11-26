#pragma once

#include <string>
#include <stack>
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
		
		/// <summary>
		/// Adds a scene to the stack and assigns it a window
		/// </summary>
		/// <param name="scene"> The scene to run. </param>
		/// <param name="windowHandle"> The handle of the window to change. </param>
		static void SwitchToScene( Scene* scene, int windowHandle );

		/// <summary>
		/// Loads a scene, adds it to the stack, and plays the stack.
		/// </summary>
		/// <param name=""></param>
		static void OpenSceneAndPlay( std::string path, int windowHandle = 0 );

	private:
		/// <summary>
		/// Completes any pending links that were created during scene loading.
		/// </summary>
		static void LinkScene();

		static std::stack<Scene*> sceneStack;
	};
}



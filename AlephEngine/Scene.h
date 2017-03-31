#pragma once
#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include "Object.h"

using namespace std;

namespace AlephEngine
{
	class Scene
	{
	private:
		GLFWwindow* window;
		void FatalError( const string& errorMessage );

	public:
		Scene();
		~Scene();
		void CreateAlephWindow( const int& width, const int& height );
		void SetWindowTitle( const string& title );
		void SetWindowIcon( const string& fileName );
		void Play();
	};
}
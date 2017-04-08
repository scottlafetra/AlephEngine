#pragma once
#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include <list>

using namespace std;

namespace AlephEngine
{
	// Forward Declarations
	class Entity;

	class Scene
	{
	private:
		static vector<Scene*> scenes;
		static vector<GLFWwindow*> windows;
		list<Entity*> entities;

		void Error( const string& errorMessage );
		void FatalError( const string& errorMessage );

	public:
		Scene();
		~Scene();
		int CreateAlephWindow( const int& width, const int& height );
		void SetWindowTitle( const string& title, const unsigned short index = 0 );
		void SetWindowIcon( const string& fileName, const unsigned short index = 0 );
		void Play();

		void AddEntity( Entity* entity );
		void DeleteEntity( Entity * entity );
		list<Entity*> GetEntities();

		Entity*         FindEntityWithTag( string tag );
		vector<Entity*> FindEntitiesWithTag( string tag );

		static void GLFWWindowClose( GLFWwindow* requestedClose );
	};
}
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
		GLFWwindow* window;
		list<Entity*> entities;

		void Error( const string& errorMessage );
		void FatalError( const string& errorMessage );

	public:
		Scene();
		~Scene();
		void CreateAlephWindow( const int& width, const int& height );
		void SetWindowTitle( const string& title );
		void SetWindowIcon( const string& fileName );
		void Play();

		void AddEntity( Entity* entity );
		void DeleteEntity( Entity * entity );
		list<Entity*> GetEntities();

		Entity*         FindEntityWithTag( string tag );
		vector<Entity*> FindEntitiesWithTag( string tag );
	};
}
#pragma once
#include <iostream>
#include <string>
#include <Matrix.h>
#include <GLFW/glfw3.h>
#include <list>

using namespace std;

namespace AlephEngine
{
	// Forward Declarations
	class Entity;
	class Renderer;
	class Camera;

	typedef void (Renderer::*RenderCallback)(GLFWwindow*, gmtl::Matrix<float, 4, 4>);

	class Scene
	{
		friend class Camera;

	private:
		static vector<Scene*> scenes;
		static vector<GLFWwindow*> windows;
		list<Entity*> entities;

		list<RenderCallback> renderCallbacks;

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

		void AddRenderCallback( RenderCallback callback );
		void RemoveRenderCallback( RenderCallback callback );
		list<RenderCallback>& GetRenderCallbacks();

		Entity*         FindEntityWithTag( string tag );
		vector<Entity*> FindEntitiesWithTag( string tag );

		static void GLFWWindowClose( GLFWwindow* requestedClose );
	};
}
#pragma once
#include <iostream>
#include <string>

#include <gmtl/Matrix.h>
#include <GLFW/glfw3.h>
#include <list>
#include <functional>

using namespace std;

namespace AlephEngine
{
	// Forward Declarations
	class Entity;
	class Renderer;
	class Camera;
	class Transform;

	class RenderCallback { public: virtual void Render() = 0; };
	class UpdateCallback { public: virtual void Update() = 0; };

	class Scene
	{
		friend class Camera;

	private:
		static bool initialized;
		static bool glewInitialized;

		static vector<Scene*> scenes;
		static vector<GLFWwindow*> windows;
		list<Entity*> entities;

		Transform* rootTransform;

		list<RenderCallback*> renderCallbacks;
		list<UpdateCallback*> updateCallbacks;

		void Error( const string& errorMessage );
		void FatalError( const string& errorMessage );

	public:
		Scene();
		~Scene();
		size_t CreateAlephWindow( const int& width, const int& height );
		void SetWindowTitle( const string& title, const unsigned short index = 0 );
		void SetWindowIcon( const string& fileName, const unsigned short index = 0 );
		void Play();

		Entity* AddEntity( const string& name );
		void DeleteEntity( Entity * entity );
		list<Entity*> GetEntities();

		// Render Callbacks
		void AddRenderCallback( RenderCallback* callback );
		void RemoveRenderCallback( RenderCallback* callback );
		list<RenderCallback*> GetRenderCallbacks();

		// Update Callbacks
		void AddUpdateCallback( UpdateCallback* callback );
		void RemoveUpdateCallback( UpdateCallback* callback );
		list<UpdateCallback*> GetUpdateCallbacks();

		Entity*         FindEntityWithTag( string tag );
		vector<Entity*> FindEntitiesWithTag( string tag );

		inline vector<GLFWwindow*> GetWindows() { return windows; }

		static void GLFWWindowClose( GLFWwindow* requestedClose );
	};
}
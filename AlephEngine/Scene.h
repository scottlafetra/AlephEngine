#pragma once
#include <iostream>
#include <string>

#include <gmtl/Matrix.h>
#include <GLFW/glfw3.h>
#include <list>
#include <functional>


namespace AlephEngine
{
	// Forward Declarations
	class Entity;
	class Renderer;
	class Camera;
	class Transform;

	
	class UpdateCallback  { public: virtual void Update() = 0; }; // Updates the game state once per frame
	class PostMoveCallback{ public: virtual void PostMove() = 0; }; // Updates that need to occur after objects have moved
	class RenderCallback { public: virtual void Render() = 0; }; // Used to call everything that should do some rendering

	class Scene
	{
		friend class Camera;

	private:
		static bool initialized;
		static bool glewInitialized;

		static std::vector<Scene*> scenes;
		static std::vector<GLFWwindow*> windows;
		std::list<Entity*> entities;

		Transform* rootTransform;

		std::list<RenderCallback*> renderCallbacks;
		std::list<UpdateCallback*> updateCallbacks;
		std::list<PostMoveCallback*> postMoveCallbacks;

		void Error( const std::string& errorMessage );
		void FatalError( const std::string& errorMessage );

	public:
		Scene();
		~Scene();
		size_t CreateAlephWindow( const int& width, const int& height );
		void SetWindowTitle( const std::string& title, const unsigned short index = 0 );
		void SetWindowIcon( const std::string& fileName, const unsigned short index = 0 );
		void Play();

		Entity* AddEntity( const std::string& name );
		void DeleteEntity( Entity * entity );
		std::list<Entity*> GetEntities();

		// Render Callbacks
		void AddRenderCallback( RenderCallback* callback );
		void RemoveRenderCallback( RenderCallback* callback );
		std::list<RenderCallback*> GetRenderCallbacks();

		// Update Callbacks
		void AddUpdateCallback( UpdateCallback* callback );
		void RemoveUpdateCallback( UpdateCallback* callback );
		std::list<UpdateCallback*> GetUpdateCallbacks();

		// Post Move Callbacks
		void AddPostMoveeCallback(PostMoveCallback* callback);
		void RemovePostMoveCallback(PostMoveCallback* callback);
		std::list<PostMoveCallback*> GetPostMoveCallbacks();

		Entity*         FindEntityWithTag(std::string tag );
		std::vector<Entity*> FindEntitiesWithTag(std::string tag );

		inline std::vector<GLFWwindow*> GetWindows() { return windows; }

		static void GLFWWindowClose( GLFWwindow* requestedClose );
	};
}
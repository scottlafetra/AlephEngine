#include <GLFW/glfw3.h>
#include <algorithm>
#include "Entity.h"
#include "Scene.h"
#include "Utility.h"

using namespace AlephEngine;

void GLFWError( int error, const char* description )
{
	cout << "GLFW Error - " << description << endl;
}

vector<Scene*> Scene::scenes;
vector<GLFWwindow*> Scene::windows;

Scene::Scene()
{
	scenes.push_back( this );
	if (!glfwInit())
	{
		FatalError( "GLFW failed to load" );
	}
	glfwSetErrorCallback( GLFWError );
}

Scene::~Scene()
{
	glfwTerminate();

	for( Entity* entity : entities )
	{
		delete entity;
	}
}

// Returns window index
int Scene::CreateAlephWindow( const int& width, const int& height )
{
	GLFWwindow* window = glfwCreateWindow( width, height, "Aleph Null", NULL, NULL );
	if ( !window )
	{
		FatalError("Window could not be created.");
	}

	glfwMakeContextCurrent( window );

	// Add to list
	unsigned short newIndex = windows.size();
	windows.push_back( window );

	// Ensure close callback is caught
	glfwSetWindowCloseCallback( window, GLFWWindowClose );

	// Default Icon
	SetWindowIcon( "AlephIcon.png" );

	return newIndex;
}

void Scene::SetWindowIcon( const string& filename, const unsigned short index )
{
	glfwSetWindowIcon( windows[index], 1, Utility::LoadGLFWImage( filename ) );
}

void Scene::SetWindowTitle( const string& title, const unsigned short index )
{
	glfwSetWindowTitle( windows[index], title.c_str() );
}

void Scene::Play()
{
	// Run until there are no more windows open
	while( windows.size() > 0 )
	{
		// Test render
		glClear( GL_COLOR_BUFFER_BIT );

		// Push render to screen
		// NOTE: all drawing will be done by camera components in the future
		glfwSwapBuffers( windows[0] );

		// Process Events
		glfwPollEvents();
	}
}

void Scene::Error( const string& errorMessage )
{
	cout << "Error - " << errorMessage << endl;
}

void Scene::FatalError( const string& errorMessage )
{
	cout << "Fatal Error - " << errorMessage << endl;
	delete this;
}

void Scene::AddEntity( Entity* entity )
{
	entity->scene = this;
	entities.push_back( entity );
}

void Scene::DeleteEntity( Entity* entity )
{
	entities.remove( entity );
	delete entity;
}

list<Entity*> Scene::GetEntities()
{
	return entities;
}

void Scene::AddRenderCallback( RenderCallback callback )
{
	renderCallbacks.push_back( callback );
}

void Scene::RemoveRenderCallback( RenderCallback callback )
{
	renderCallbacks.remove( callback );
}

list<RenderCallback>& Scene::GetRenderCallbacks()
{
	return renderCallbacks;
}

// Returns NULL if not found
Entity* Scene::FindEntityWithTag( string tag )
{
	 auto result = find_if( entities.begin(), entities.end(), [&]( const Entity* entity ) { return entity->tag == tag; } );

	 // Check for error
	 if( result == entities.end() )
	 {
		 return NULL;
	 }

	 return *result;
}

vector<Entity*> Scene::FindEntitiesWithTag( string tag )
{
	auto checkTag = [&]( const Entity* entity ) { return entity->tag.compare(tag) == 0; };
	auto end = entities.end();
	auto current = find_if( entities.begin(), end,  checkTag);
	vector<Entity*> results;

	while( current != end )
	{
		results.push_back( *current );
		current++;

		current = find_if( current, end, checkTag );
	}

	return results;
}

void Scene::GLFWWindowClose( GLFWwindow* requestedClose )
{
	// Close window
	windows.erase( remove( windows.begin(), windows.end(), requestedClose ), windows.end() );
	glfwDestroyWindow( requestedClose );
}
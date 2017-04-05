#include <GLFW/glfw3.h>
#include <algorithm>
#include "Entity.h"
#include "Scene.h"
#include "Utility.h"

using namespace AlephEngine;
	
Scene::Scene()
{
	if (!glfwInit())
	{
		FatalError( "GLFW failed to load" );
	}
}

Scene::~Scene()
{
	glfwTerminate();

	for( Entity* entity : entities )
	{
		delete entity;
	}
}

void Scene::CreateAlephWindow( const int& width, const int& height )
{
	window = glfwCreateWindow( width, height, "Aleph Null", NULL, NULL );
	if ( !window )
	{
		FatalError("Window could not be created.");
	}

	glfwMakeContextCurrent( window );

	// Default Icon
	SetWindowIcon( "AlephIcon.png" );
}

void Scene::SetWindowIcon( const string& filename )
{
	glfwSetWindowIcon( window, 1, Utility::LoadGLFWImage( filename ) );
}

void Scene::SetWindowTitle( const string& title )
{
	glfwSetWindowTitle( window, title.c_str() );
}

void Scene::Play()
{
	// Run until close
	while( !glfwWindowShouldClose( window ) )
	{
		// Test render
		glClear( GL_COLOR_BUFFER_BIT );

		// Push render to screen
		glfwSwapBuffers( window );

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
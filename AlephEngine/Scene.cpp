#include "Scene.h"
#include "Utility.h"
#include <GLFW/glfw3.h>
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

void Scene::FatalError( const string& errorMessage )
{
	cout << "Fatal Error - " << errorMessage << endl;
	delete this;
}
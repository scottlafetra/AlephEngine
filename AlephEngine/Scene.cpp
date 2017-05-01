#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include "Entity.h"
#include "Utility.h"
#include "Transform.h"
#include "Scene.h"
#include "EngineTime.h"

using namespace AlephEngine;

// Ripped from some tutorial TODO: Read
void APIENTRY glDebugOutput( GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar *message,
	void *userParam )
{
	// ignore non-significant error/warning codes
	//if( id == 131169 || id == 131185 || id == 131218 || id == 131204 ) return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch( source )
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch( type )
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch( severity )
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;
}

void GLFWError( int error, const char* description )
{
	cout << "GLFW Error - " << description << endl;
}

vector<Scene*> Scene::scenes;
vector<GLFWwindow*> Scene::windows;

bool Scene::initialized = false;
bool Scene::glewInitialized = false;

Scene::Scene()
	: rootTransform( new Transform( NULL ) )
{
	scenes.push_back( this );

	if( !initialized )
	{
		glfwSetErrorCallback( GLFWError );
		if( !glfwInit() )
		{
			FatalError( "GLFW failed to load" );
		}
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

// Returns window index
size_t Scene::CreateAlephWindow( const int& width, const int& height )
{
	glfwWindowHint( GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE );
	GLFWwindow* window = glfwCreateWindow( width, height, "Aleph Null", NULL, NULL );
	if ( !window )
	{
		FatalError("Window could not be created.");
	}
	
	glfwMakeContextCurrent( window );
	glfwSwapInterval( 1 ); // Vsync
	
	if( !glewInitialized )
	{
		GLenum glewError;
		if( ( glewError = glewInit() ) != GLEW_OK )
		{
			printf( "%s\n", glewGetErrorString( glewError ) );
			FatalError( "GLEW failed to load" );
		}

		//TODO: Evaluate nessesity
		glEnable( GL_DEPTH_TEST );
		glDisable( GL_CULL_FACE );
		glEnableClientState( GL_VERTEX_ARRAY );
	}

	// Init debug
	GLint flags;
	glGetIntegerv( GL_CONTEXT_FLAGS, &flags );
	if( flags & GL_CONTEXT_FLAG_DEBUG_BIT )
	{
		glEnable( GL_DEBUG_OUTPUT );
		glEnable( GL_DEBUG_OUTPUT_SYNCHRONOUS );
		glDebugMessageCallback( (GLDEBUGPROC) glDebugOutput, nullptr );
		glDebugMessageControl( GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE );
	}
	else
	{
		cout << "Warning: Couldn't create OpenGL debug context." << endl;
	}

	// Version number
	cout << "Using OpenGL " << glGetString( GL_VERSION ) << endl;

	// Add to list
	size_t newIndex = windows.size();
	windows.push_back( window );

	// Ensure close callback is caught
	glfwSetWindowCloseCallback( window, GLFWWindowClose );

	// Default Icon
	SetWindowIcon( "AlephIcon.png" );

	glClearColor( 0 / 255.f, 102 / 255.f, 255/255.f, 1.0f );

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
	// Reset time
	glfwSetTime( 0 );

	// Run until there are no more windows open
	while( windows.size() > 0 )
	{
		EngineTime::UpdateTimes();

		// Call component updates
		for(UpdateCallback* updateCallback : updateCallbacks)
		{
			updateCallback->Update();
		}

		// Render
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		for( RenderCallback* renderCallback : renderCallbacks )
		{
			renderCallback->Render();
		}

		// Push render to screen
		glfwSwapBuffers( windows[ 0 ] );

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

Entity* Scene::AddEntity( const string& name )
{
	Entity* entity = new Entity( name );
	entity->scene = this;
	entities.push_back( entity );

	// Add to root if neccisary
	Transform* transform = entity->FetchComponent<Transform>();	
	if( transform->GetParent() == NULL )
	{
		transform->SetAsParent( rootTransform );
	}

	return entity;
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

void Scene::AddRenderCallback( RenderCallback* callback ) { renderCallbacks.push_back( callback ); }
void Scene::AddUpdateCallback( UpdateCallback* callback ) { updateCallbacks.push_back( callback ); }

void Scene::RemoveRenderCallback( RenderCallback* callback ) { renderCallbacks.remove( callback ); }
void Scene::RemoveUpdateCallback( UpdateCallback* callback ) { updateCallbacks.remove( callback ); }

list<RenderCallback*> Scene::GetRenderCallbacks() { return renderCallbacks; }
list<UpdateCallback*> Scene::GetUpdateCallbacks() { return updateCallbacks; }

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
	// GLFW handles actual window closure unless we say otherwise
}
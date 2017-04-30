#pragma once
#include <cstdlib>
#include <string>
#include "MeshRenderer.h"
#include "Component.h"
#include "Camera.h"
#include "Rotates.h"


#include "Transform.h"
using namespace std;
using namespace AlephEngine;

// Make testcube life easier
//				Name				       Verticies
#define CUBE_VERT_FRONT_BOTTOM_RIGHT   0.5f,  0.5f,  0.5f
#define CUBE_VERT_FRONT_BOTTOM_LEFT    0.5f,  0.5f, -0.5f
#define CUBE_VERT_FRONT_TOP_RIGHT      0.5f, -0.5f,  0.5f
#define CUBE_VERT_FRONT_TOP_LEFT       0.5f, -0.5f, -0.5f
#define CUBE_VERT_BACK_BOTTOM_RIGHT   -0.5f,  0.5f,  0.5f
#define CUBE_VERT_BACK_BOTTOM_LEFT    -0.5f,  0.5f, -0.5f
#define CUBE_VERT_BACK_TOP_RIGHT      -0.5f, -0.5f,  0.5f
#define CUBE_VERT_BACK_TOP_LEFT       -0.5f, -0.5f, -0.5f

// Colors		  RGB data
#define RED		1.f, 0.f, 0.f
#define GREEN	0.f, 1.f, 0.f
#define BLUE	0.f, 0.f, 1.f

#define CYAN	0.f, 1.f, 1.f
#define MAGENTA	1.f, 0.f, 1.f
#define YELLOW	1.f, 1.f, 0.f

static const struct
{
	float x, y, z;			float r, g, b;
}
testTri[ 3 ] =
{//	      Verticies             Colors
	{ -0.6f, -0.4f, 0.f,	1.f, 0.f, 0.f },
	{  0.6f, -0.4f, 0.f,	0.f, 1.f, 0.f },
	{   0.f,  0.6f, 0.f,	0.f, 0.f, 1.f }
},
testCube[ 3*2*6 ] =
{
	// Face 1
	{ CUBE_VERT_FRONT_TOP_LEFT,		RED },
	{ CUBE_VERT_FRONT_BOTTOM_LEFT,	RED },
	{ CUBE_VERT_FRONT_BOTTOM_RIGHT,	RED },
	  
	{ CUBE_VERT_FRONT_BOTTOM_RIGHT,	RED },
	{ CUBE_VERT_FRONT_TOP_RIGHT,	RED },
	{ CUBE_VERT_FRONT_TOP_LEFT,		RED },
	
	// Face 2
	{ CUBE_VERT_FRONT_BOTTOM_LEFT,	GREEN },
	{ CUBE_VERT_BACK_BOTTOM_LEFT,	GREEN },
	{ CUBE_VERT_BACK_BOTTOM_RIGHT,	GREEN },
	  
	{ CUBE_VERT_BACK_BOTTOM_RIGHT,	GREEN },
	{ CUBE_VERT_FRONT_BOTTOM_RIGHT,	GREEN },
	{ CUBE_VERT_FRONT_BOTTOM_LEFT,	GREEN },
	
	// Face 3
	{ CUBE_VERT_FRONT_TOP_RIGHT,	BLUE },
	{ CUBE_VERT_FRONT_BOTTOM_RIGHT, BLUE },
	{ CUBE_VERT_BACK_BOTTOM_RIGHT,	BLUE },
	  
	{ CUBE_VERT_BACK_BOTTOM_RIGHT,	BLUE },
	{ CUBE_VERT_BACK_TOP_RIGHT,		BLUE },
	{ CUBE_VERT_FRONT_TOP_RIGHT,	BLUE },
	
	// Face 4
	{ CUBE_VERT_FRONT_TOP_LEFT,		CYAN },
	{ CUBE_VERT_BACK_TOP_LEFT,		CYAN },
	{ CUBE_VERT_BACK_BOTTOM_LEFT,	CYAN },
	  
	{ CUBE_VERT_BACK_BOTTOM_LEFT,	CYAN },
	{ CUBE_VERT_FRONT_BOTTOM_LEFT,	CYAN },
	{ CUBE_VERT_FRONT_TOP_LEFT,		CYAN },
	
	// Face 5
	{ CUBE_VERT_FRONT_TOP_LEFT,		MAGENTA },
	{ CUBE_VERT_FRONT_TOP_RIGHT,	MAGENTA },
	{ CUBE_VERT_BACK_TOP_RIGHT,		MAGENTA },
	 
	{ CUBE_VERT_BACK_TOP_RIGHT,		MAGENTA },
	{ CUBE_VERT_BACK_TOP_LEFT,		MAGENTA },
	{ CUBE_VERT_FRONT_TOP_LEFT,		MAGENTA },
	
	// Face 6
	{ CUBE_VERT_BACK_TOP_LEFT,		YELLOW },
	{ CUBE_VERT_BACK_TOP_RIGHT,		YELLOW },
	{ CUBE_VERT_BACK_BOTTOM_RIGHT,	YELLOW },
	  
	{ CUBE_VERT_BACK_BOTTOM_RIGHT,	YELLOW },
	{ CUBE_VERT_BACK_BOTTOM_LEFT,	YELLOW },
	{ CUBE_VERT_BACK_TOP_LEFT,		YELLOW }
};

// Test Components
class Tester1 : public Component
{
public:
	Tester1( Entity* entity )
		: Component( entity, Type<Tester1>() )
	{
	}

	void CauseError()
	{
		Error( "Tester1 Error" );
	}
};

class Tester2 : public Component
{
public:
	Tester2( Entity* entity )
		: Component( entity, Type<Tester2>() )
	{
	}

	void CauseFatalError()
	{
		FatalError( "Tester2 Fatal Error" );
	}
};

void PrintScene( Scene* scene )
{
	// Print contents of scene
	for( Entity* entity : scene->GetEntities() )
	{
		cout << "\nName: " << entity->GetName() << endl;
		cout << "ID: " << entity->GetID() << endl;
		cout << "Components:" << endl;

		for( Component* component : entity->GetComponents() )
		{
			cout << "\t" << component->GetTypeName() << endl;
		}
	}
}

void ECSTest()
{
	// Create the scene
	Scene scene;

	// Setup the window for mex stress
	scene.CreateAlephWindow( 800, 600 );
	scene.SetWindowTitle( "ECS Test" );

	// Add test entities and componets
	for( int eNum = 0; eNum < 10; ++eNum )
	{
		Entity* entity = scene.AddEntity( string("Test Entity ") + string(1, 'A' + eNum ) );
		entity->tag = to_string(eNum % 3);
	}

	for( Entity* entity : scene.FindEntitiesWithTag( "0" ) )
	{
		entity->AddComponent<Tester1>();
	}

	for( Entity* entity : scene.FindEntitiesWithTag( "1" ) )
	{
		entity->AddComponent<Tester2>();
	}

	for( Entity* entity : scene.FindEntitiesWithTag( "2" ) )
	{
		entity->AddComponent<Tester1>();
		entity->AddComponent<Tester2>();
	}

	PrintScene( &scene );

	// Gennerate errors
	cout << "\nCausing an error on the Tester1 Compoent on Entity A" << endl;
	scene.GetEntities().front()->FetchComponent<Tester1>()->CauseError();

	cout << "\nCausing a fatal error on the Tester2 Compoent on Entity B" << endl;
	scene.FindEntitiesWithTag( "1" ).front()->FetchComponent<Tester2>()->CauseFatalError();

	cout << "\nNow note how Tester2 on entity B deleted itsself.\n" << endl;

	PrintScene( &scene );

	// Play the scene
	scene.Play();
}

void RenderTest()
{
	// Create the scene
	Scene scene;

	// Setup the window
	scene.CreateAlephWindow( 800, 600 );
	scene.SetWindowTitle( "Render Test" );
	
	// Load Camera
	Entity* camera = scene.AddEntity( "Camera" );

	camera->AddComponent<Camera>();
	camera->FetchComponent<Camera>()->SetPerspective( 45, 1, 20 );
	

	

	// Load test cube
	Entity* testRenderCube = scene.AddEntity( "TestRenderCube" );

	MeshRenderer<Shaders::StdUnlit>* cubeRenderer = testRenderCube->AddComponent<MeshRenderer<Shaders::StdUnlit>>();
	cubeRenderer->SetVertices( GL_TRIANGLES, 3 * 2 * 6, (GLfloat*) testCube );
	

	testRenderCube->FetchComponent<Transform>()->Move(-1, 0, -4 );

	testRenderCube->AddComponent<Rotates>();
	testRenderCube->FetchComponent<Rotates>()->SetSpeed(0.f, 0.6f, 0.5);
	
	// Load test tri
	Entity* testRenderTri = scene.AddEntity( "TestRenderTri" );

	MeshRenderer<Shaders::StdUnlit>* triRenderer = testRenderTri->AddComponent<MeshRenderer<Shaders::StdUnlit>>();
	triRenderer->SetVertices( GL_TRIANGLES, 3, (GLfloat*) testTri );

	testRenderTri->FetchComponent<Transform>()->Move( 1, 0, -4 );

	testRenderTri->AddComponent<Rotates>();
	testRenderTri->FetchComponent<Rotates>()->SetSpeed( 0.f, -0.5f, -0.6f );
	
	

	PrintScene( &scene );
	
	// Play the scene
	scene.Play();
}

int main(int argn, char* argc[])
{
	//ECSTest();
	RenderTest();

	//Scene is deleted on end
	return EXIT_SUCCESS;
}
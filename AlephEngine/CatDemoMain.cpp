#pragma once
#include <cstdlib>
#include <string>
#include "MeshRenderer.h"
#include "Component.h"
#include "Camera.h"
#include "Rotates.h"
#include "CatMotion.h"
#include "Transform.h"
#include "ctime"


using namespace std;
using namespace AlephEngine;

#include "Testing.h"


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
	camera->FetchComponent<Transform>()->Move( 0, 0, 2 );
	

	
	
	// Load test cube
	Entity* testRenderCube = scene.AddEntity( "TestRenderCube" );

	MeshRenderer<Shaders::StdUnlit>* cubeRenderer = testRenderCube->AddComponent<MeshRenderer<Shaders::StdUnlit>>();
	cubeRenderer->SetVertices( GL_TRIANGLES, 3 * 2 * 6, (GLfloat*) testCube );

	testRenderCube->FetchComponent<Transform>()->Move( 0, 0, -4 );

	testRenderCube->AddComponent<Rotates>();
	testRenderCube->FetchComponent<Rotates>()->SetSpeed(0.f, 0.6f, 0.5);
	
	///*
	// Load cat cube
	Entity* catRenderCube = scene.AddEntity( "TestCatCube" );

	MeshRenderer<Shaders::UnlitTexture>* catRenderer = catRenderCube->AddComponent<MeshRenderer<Shaders::UnlitTexture>>();
	GLFWimage* catTexture = Utility::LoadGLFWImage( "CatTexture.png" );
	catRenderer->SetVertices( GL_TRIANGLES, 3 * 2 * 6, (GLfloat*) catCube );
	catRenderer->SetTexture( catTexture, GL_CLAMP_TO_BORDER );

	catRenderCube->FetchComponent<Transform>()->Move( 2, 0, -4 );
	
	catRenderCube->AddComponent<Rotates>();
	catRenderCube->FetchComponent<Rotates>()->SetSpeed( 0.5f, 0.7f, 0.f );
	//*/
	// Load test tri
	Entity* testRenderTri = scene.AddEntity( "TestRenderTri" );

	MeshRenderer<Shaders::StdUnlit>* triRenderer = testRenderTri->AddComponent<MeshRenderer<Shaders::StdUnlit>>();
	triRenderer->SetVertices( GL_TRIANGLES, 3, (GLfloat*) testTri );

	testRenderTri->FetchComponent<Transform>()->Move( -2, 0, -4 );

	testRenderTri->AddComponent<Rotates>();
	testRenderTri->FetchComponent<Rotates>()->SetSpeed( 0.f, -0.5f, -0.6f );
	
	

	PrintScene( &scene );
	
	// Play the scene
	scene.Play();
}

void LoadCat( string name, Scene* scene, GLFWimage* texture, float xPos = 0, float yPos = 0 )
{
	// Load cat cube
	Entity* catRenderCube = scene->AddEntity( name );

	MeshRenderer<Shaders::UnlitTexture>* catRenderer = catRenderCube->AddComponent<MeshRenderer<Shaders::UnlitTexture>>();
	catRenderer->SetVertices( GL_TRIANGLES, 3 * 2 * 6, (GLfloat*) catCube );
	catRenderer->SetTexture( texture, GL_CLAMP_TO_BORDER );

	catRenderCube->FetchComponent<Transform>()->Move( -5, yPos, -3 );
	catRenderCube->FetchComponent<Transform>()->Scale( ( rand() % 100 ) / 100.f + 0.2 );

	catRenderCube->AddComponent<Rotates>();
	catRenderCube->FetchComponent<Rotates>()->SetSpeed( 
		(rand() % 200 - 100)/100.f,
		( rand() % 200 - 100 ) / 100.f,
		( rand() % 200 - 100 ) / 100.f );

	catRenderCube->AddComponent<CatMotion>();
	catRenderCube->FetchComponent<CatMotion>()->SetSpeed( ( rand() % 150 - 75 ) / 100.f + 1.f);
	catRenderCube->FetchComponent<CatMotion>()->SetLimit( 5 );
}

void CatDemo( void )
{
	// Init rand
	srand( time(0) );

	// Create the scene
	Scene scene;

	// Setup the window
	scene.CreateAlephWindow( 1152, 648 );
	scene.SetWindowTitle( "The Cat's Meow" );

	// Load Camera
	Entity* camera = scene.AddEntity( "Camera" );

	camera->AddComponent<Camera>();
	camera->FetchComponent<Camera>()->SetPerspective( 45, 1, 20 );
	camera->FetchComponent<Transform>()->Move( 0, 0, 2 );
	
	// Load Background
	Entity* background = scene.AddEntity( "Background" );

	MeshRenderer<Shaders::UnlitTexture>* backgroundRenderer = background->AddComponent<MeshRenderer<Shaders::UnlitTexture>>();
	GLFWimage* catBackground = Utility::LoadGLFWImage( "catBackground.png" );
	backgroundRenderer->SetVertices( GL_TRIANGLES, 6, (GLfloat*) texQuad );
	backgroundRenderer->SetTexture( catBackground, GL_CLAMP_TO_BORDER );

	background->FetchComponent<Transform>()->Move( 0, 0, -10 );
	background->FetchComponent<Transform>()->SetScale( 11 );


	// Load Cats
	float yPos = -3;
	int yIncrement = 1.3f;

	GLFWimage* catTex[ 3 ];
	catTex[ 0 ] = Utility::LoadGLFWImage( "CatTexture.png" );
	catTex[ 1 ] = Utility::LoadGLFWImage( "KitCat.png" );
	catTex[ 2 ] = Utility::LoadGLFWImage( "KalynCat.png" );

	for(int i = 0; i < 5; ++i)
	{
		yPos += yIncrement + ( rand() % 100 ) / 200.f - 0.25f;
		LoadCat( "Cat", &scene, catTex[ rand() % 3 ], -( rand()% 500 )/ 100.f - 4,  yPos );
	}

	yPos = -3;
	for(int i = 0; i < 5; ++i)
	{
		yPos += yIncrement + ( rand() % 100 ) / 200.f - 0.25f;
		LoadCat( "Cat", &scene, catTex[ rand() % 3 ], -( rand() % 500 ) / 100.f - 6, yPos );
	}
	

	// Play the scene
	scene.Play();
}

int WinMain(int argn, char* argc[])
{
	//ECSTest();
	//RenderTest();
	CatDemo();

	//Scene is deleted on end
	return EXIT_SUCCESS;
}
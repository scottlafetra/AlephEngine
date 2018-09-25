#pragma once
#include <cstdlib>
#include <string>
#include "../Rendering/MeshRenderer.h"
#include "../Core/Component.h"
#include "../Rendering/Camera.h"
#include "../Rotates.h"
#include "CatMotion.h"
#include "../Core/Transform.h"
#include <ctime>
#include "../Physics/Kinematics.h"
#include "CatGravity.h"
#include "../Physics/Collision.h"
#include <cmath>
#include <vector>


using namespace AlephEngine;

#include "Testing.h"


void PrintScene( Scene* scene )
{
	// Print contents of scene
	for( Entity* entity : scene->GetEntities() )
	{
		std::cout << "\nName: " << entity->GetName() << std::endl;
		std::cout << "ID: " << entity->GetID() << std::endl;
		std::cout << "Components:" << std::endl;

		for( Component* component : entity->GetComponents() )
		{
			std::cout << "\t" << component->GetTypeName() << std::endl;
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
		Entity* entity = scene.AddEntity(std::string("Test Entity ") + std::string(1, 'A' + eNum ) );
		entity->tag = std::to_string(eNum % 3);
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
	std::cout << "\nCausing an error on the Tester1 Compoent on Entity A" << std::endl;
	scene.GetEntities().front()->FetchComponent<Tester1>()->CauseError();

	std::cout << "\nCausing a fatal error on the Tester2 Compoent on Entity B" << std::endl;
	scene.FindEntitiesWithTag( "1" ).front()->FetchComponent<Tester2>()->CauseFatalError();

	std::cout << "\nNow note how Tester2 on entity B deleted itsself.\n" << std::endl;

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

void LoadCat(std::string name, Scene* scene, GLFWimage* texture, float xPos = 0, float yPos = 0, float zPos = 0)
{
	// Load cat cube
	Entity* catRenderCube = scene->AddEntity( name );

	MeshRenderer<Shaders::UnlitTexture>* catRenderer = catRenderCube->AddComponent<MeshRenderer<Shaders::UnlitTexture>>();
	catRenderer->SetVertices( GL_TRIANGLES, 3 * 2 * 6, (GLfloat*) catCube );
	catRenderer->SetTexture( texture, GL_CLAMP_TO_BORDER );

	catRenderCube->FetchComponent<Transform>()->Move( xPos, yPos, -3 + zPos );
	float scale = (rand() % 100) / 100.f + 0.2;
	catRenderCube->FetchComponent<Transform>()->Scale( scale );
	
	catRenderCube->AddComponent<Rotates>();
	catRenderCube->FetchComponent<Rotates>()->SetSpeed( 
		(rand() % 200 - 100)/100.f,
		( rand() % 200 - 100 ) / 100.f,
		( rand() % 200 - 100 ) / 100.f );


	catRenderCube->AddComponent<Kinematics>()->mass = scale;
	//catRenderCube->AddComponent<CatMotion>();
	//catRenderCube->FetchComponent<CatMotion>()->SetSpeed( ( rand() % 150 - 75 ) / 100.f + 1.f);
	//catRenderCube->FetchComponent<CatMotion>()->SetLimit( 5, 3 );
	
	catRenderCube->AddComponent<Gravity>();
	catRenderCube->AddComponent<CatGravity>();

	catRenderCube->AddComponent<Collider>()->SetMesh( std::vector<float>( (float*) catCube, (float*) catCube + 3 * 2 * 6 ) );
}

void CatDemo( void )
{
	std::cout << "Starting Cat Demo" << std::endl;
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
	camera->FetchComponent<Camera>()->SetPerspective( 45, 1, 1000);
	camera->FetchComponent<Transform>()->Move( 0, 0, 2 );
	
	// Load Background
	Entity* background = scene.AddEntity( "Background" );

	MeshRenderer<Shaders::UnlitTexture>* backgroundRenderer = background->AddComponent<MeshRenderer<Shaders::UnlitTexture>>();
	GLFWimage* catBackground = Utility::LoadGLFWImage( "catBackground.png" );
	backgroundRenderer->SetVertices( GL_TRIANGLES, 6, (GLfloat*) texQuad );
	backgroundRenderer->SetTexture( catBackground, GL_CLAMP_TO_BORDER );

	background->FetchComponent<Transform>()->Move( 0, 0, -18);
	background->FetchComponent<Transform>()->SetScale( 18 );


	// Load Cats

	GLFWimage* catTex[3];
	catTex[0] = Utility::LoadGLFWImage("CatTexture.png");
	catTex[1] = Utility::LoadGLFWImage("KitCat.png");
	catTex[2] = Utility::LoadGLFWImage("KalynCat.png");

	// Circle spawn
	float radius = 2;
	int maxCats = 6;
	float angle = 0;
	for (int catNum = 0; catNum < maxCats; ++catNum)
	{
		
		LoadCat("Cat", &scene, catTex[rand() % 3], cos(angle) * radius,  sin(angle) * radius,  -((rand() % 3000 ) / 1000.0)  );

		angle += ((2*3.14) / maxCats);
	}



	/* Outdated line cat method
	float yPos = -3;
	int yIncrement = 1.3f;

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
	*/
	
	// set gravity to be resonable
	Gravity::G = 0.01;
	Gravity::maxImpulse = 80;

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

int main(int argn, char* argc[])
{
	//ECSTest();
	//RenderTest();
	CatDemo();

	//Scene is deleted on end
	return EXIT_SUCCESS;
}
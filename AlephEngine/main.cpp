#pragma once
#include <cstdlib>
#include <string>
#include "Component.h"
using namespace std;
using namespace AlephEngine;

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

		cout << "Has Tester1?: ";
		Component* component = entity->FetchComponent<Tester1>();
		if( component == NULL )
		{
			cout << "No" << endl;
		}
		else
		{
			cout << component->GetTypeName() << endl;
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
		Entity* entity = new Entity( string("Test Entity ") + string(1, 'A' + eNum ) );
		entity->tag = to_string(eNum % 3);
		scene.AddEntity( entity );
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

int main(int argn, char* argc[])
{
	ECSTest();
	
	//Scene is deleted on end
	return EXIT_SUCCESS;
}
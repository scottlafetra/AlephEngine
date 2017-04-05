#include "Entity.h"
using namespace AlephEngine;

unsigned int Entity::nextId = 0;

Entity::Entity( string name )
	: id( nextId ), name( name ), scene( NULL )
{
	nextId++;
}

Entity::~Entity()
{
	for( Component* component : components )
	{
		delete component;
	}
}

string Entity::GetName() const
{
	return name;
}

unsigned int Entity::GetID() const
{
	return id;
}

list<Component*> Entity::GetComponents()
{
	return components;
}

Scene* Entity::GetScene() const
{
	return scene;
}

void Entity::Error( string errorMessage )
{
	cout << "Error - " << errorMessage << " in entity #" << GetID()
		<< "( \"" << GetName() << "\" )" << endl;
}

void Entity::FatalError( string errorMessage )
{
	cout << "Fatal Error - " << errorMessage << " in entity #" << GetID()
		<< "( \"" << GetName() << "\" )" << endl;

	scene->DeleteEntity( this );
}

void Entity::DeleteComponent( Component* toDelete )
{
	if( toDelete == NULL )
	{
		Error( "Could not delete compoment passed to \"DeleteComponent()\"" );
	}
	else
	{
		components.remove( toDelete );
		delete toDelete;
	}
}




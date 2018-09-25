#include "Entity.h"
#include "../Physics/Kinematics.h"
#include "Transform.h"
using namespace AlephEngine;

unsigned int Entity::nextId = 0;

/// <summary>
/// Entity ctor.
/// </summary>
/// <param name="name">Name to give the entity.</param>
Entity::Entity(std::string name )
	: id( nextId ), name( name ), scene( NULL ), renderMe( false ), renderable( false )
{
	nextId++;

	// All entities have a Transform
	AddComponent<Transform>();
}

/// <summary>
/// Enity dtor.
/// </summary>
Entity::~Entity()
{
	// Remove a kinematics from scene if possible
	if (FetchComponent<Kinematics>() != NULL)
	{
		DeleteComponent<Kinematics>();
	}

	for( Component* component : components )
	{
		delete component;
	}
}

/// <summary>
/// Get the name of the Enity.
/// </summary>
/// <returns>The name of the Enity.</returns>
std::string Entity::GetName() const
{
	return name;
}

/// <summary>
/// Get the unique id of the entity.
/// </summary>
/// <returns>The unique id of the entity.</returns>
unsigned int Entity::GetID() const
{
	return id;
}

/// <summary>
/// Get the components attached to this entity.
/// </summary>
/// <returns>A list of the components attached to this entity.</returns>
std::list<Component*> Entity::GetComponents()
{
	return components;
}

/// <summary>
/// Get the scene this entity exists in.
/// </summary>
/// <returns>The scene this entity exists in.</returns>
Scene* Entity::GetScene() const
{
	return scene;
}

/// <summary>
/// Log a non-fatal error.
/// </summary>
/// <param name="errorMessage">A description of the error.</param>
void Entity::Error(std::string errorMessage )
{
	std::cout << "Error - " << errorMessage << " in entity #" << GetID()
		<< "( \"" << GetName() << "\" )" << std::endl;
}

/// <summary>
/// Log a fatal error. The entity will be removed as it can't continue running.
/// </summary>
/// <param name="errorMessage">A description of the error.</param>
void Entity::FatalError(std::string errorMessage )
{
	std::cout << "Fatal Error - " << errorMessage << " in entity #" << GetID()
		<< "( \"" << GetName() << "\" )" << std::endl;

	scene->DeleteEntity( this );
}

/// <summary>
/// Delete a component from this entity.
/// </summary>
/// <param name="toDelete">The component to delete.</param>
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




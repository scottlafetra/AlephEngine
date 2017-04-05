#pragma once
using namespace AlephEngine;

// May only use one of each type of component
template <class T>
T* Entity::AddComponent()
{
	if( FetchComponent<T>() != NULL )
	{
		Error( string( "Could not add component of type " ) + Component::TypeName<T>() );
	}

	T* newComponent = new T( this );

	components.push_back( newComponent );

	return newComponent;
}

template <class T>
T* Entity::FetchComponent()
{
	auto sameType = []( const Component* component ) { return component->GetType() == Component::Type<T>(); };

	auto end = components.end();
	auto result =  find_if( components.begin(), end, sameType );

	if( result == end )
	{
		return NULL;
	}
	else
	{
		return static_cast<T*>( *result );
	}
}

template <class T>
void Entity::DeleteComponent()
{
	T* toDelete = FetchComponent<T>();

	if( toDelete == NULL )
	{
		scene.Error( "Could not delete compoment of type " + Component::TypeName<T>() );
	}
	else
	{
		components.remove( toDelete );
		delete toDelete;
	}
}
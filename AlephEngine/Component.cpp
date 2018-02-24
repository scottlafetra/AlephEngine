#include "Component.h"
using namespace std;
using namespace AlephEngine;

unordered_map< size_t, CType > Component::issuedTypes;
unordered_map< CType, string > Component::typeNames;
CType Component::nextType = 0;

/// <summary>
/// Component cotr.
/// </summary>
/// <param name="entity">The entity to attach this component to.</param>
/// <param name="type">The unique identifier number for this component type.</param>
Component::Component( Entity* entity, CType type )
	: isActive( true ), entity( entity ), type( type ) {}

/// <summary>
/// Log a non-fatal error message.
/// </summary>
/// <param name="errorMessage">A description of the error.</param>
void Component::Error( const string& errorMessage )
{
	cout << "Error - " << errorMessage << " in entity #" << entity->GetID()
		<< "( \"" << GetTypeName() << "\" on \"" << entity->GetName() << "\" )" << endl;;
}

/// <summary>
/// Log a fatal error. The entity will be removed since it cannot continue to run.
/// </summary>
/// <param name="errorMessage">A description of the error.</param>
void Component::FatalError( const string& errorMessage )
{
	cout << "Fatal Error - " << errorMessage << " in entity #" << entity->GetID()
		<< "( \"" << GetTypeName() << "\" on \"" << entity->GetName() << "\" )" << endl;;

	entity->DeleteComponent(this);
}

/// <summary>
/// Returns the unique indentifier for this component type.
/// </summary>
/// <returns>The unique indentifier for this component type.</returns>
CType Component::GetType() const
{
	return type;
}

/// <summary>
/// Get the human readable name for this component type.
/// </summary>
/// <returns>The human readable name for this component type.</returns>
string Component::GetTypeName() const
{
	return typeNames[ type ];
}



		
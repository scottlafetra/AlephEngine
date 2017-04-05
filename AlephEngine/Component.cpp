#include "Component.h"
using namespace AlephEngine;

unordered_map< size_t, CType > Component::issuedTypes;
unordered_map< CType, string > Component::typeNames;
CType Component::nextType = 0;

Component::Component( Entity* entity, unsigned int type )
	: isActive( true ), entity( entity ), type( type ) {}

void Component::Error( const string& errorMessage )
{
	cout << "Error - " << errorMessage << " in entity #" << entity->GetID()
		<< "( \"" << GetTypeName() << "\" on \"" << entity->GetName() << "\" )" << endl;;
}

void Component::FatalError( const string& errorMessage )
{
	cout << "Fatal Error - " << errorMessage << " in entity #" << entity->GetID()
		<< "( \"" << GetTypeName() << "\" on \"" << entity->GetName() << "\" )" << endl;;

	entity->DeleteComponent(this);
}

inline Scene* Component::GetScene() { return entity->GetScene(); }

CType Component::GetType() const
{
	return type;
}

string Component::GetTypeName() const
{
	return typeNames[ type ];
}



		
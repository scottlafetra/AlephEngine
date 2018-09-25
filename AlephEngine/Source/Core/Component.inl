#pragma once
using namespace AlephEngine;

template <class T>
static CType Component::Type()
{
	CType type;

	if( issuedTypes.count( typeid(T).hash_code() ) == 0 )//if CType has not been issued yet
	{
		//issue a new CType into issuedTypes
		issuedTypes[typeid(T).hash_code()] = type = nextType;

		// find and store the name
		std::string name = typeid(T).name();
		size_t start = name.find_last_of( ":" ) + 1;

		typeNames[type] = name.substr( start, name.length() - start );
		
		nextType++;
	}
	else
	{
		type = issuedTypes[typeid(T).hash_code()];
	}

	return type;
}

template <class T>
static std::string Component::TypeName()
{
	return typeNames[Type<T>()];
}
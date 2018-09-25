#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include "Entity.h"

namespace AlephEngine
{
	typedef unsigned int CType;

	class Component
	{
	public:
		bool isActive;

	protected:
		Entity* entity;

	private:
		static std::unordered_map< size_t, CType  > issuedTypes;
		static std::unordered_map< CType, std::string > typeNames;
		static CType nextType;

		unsigned int type;

	protected:
		void Error( const std::string& errorMessage );
		void FatalError( const std::string& errorMessage );

	public:
		Component( Entity* entity, CType type );
		virtual inline ~Component() {};

		inline Entity* GetEntity() const { return entity; }
		inline Scene* GetScene() { return entity->GetScene(); }
		CType GetType() const;
		std::string GetTypeName() const;
		template <class T> static CType Type();
		template <class T> static std::string TypeName();
	};
}

#include "Component.inl"

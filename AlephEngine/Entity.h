#pragma once
#include <vector>
#include <algorithm>
#include "Scene.h"
using namespace std;

namespace AlephEngine
{
	// Forward Declarations
	class Component;

	class Entity
	{
		friend class Scene;

	public:
		string tag;

	private:
		string name;
		unsigned int id;
		static unsigned int nextId;
		list<Component*> components;
		Scene* scene;

	protected:
		void Error( string errorMessage );
		void FatalError( string errorMessage );

	public:
		Entity( string name );
		~Entity();

		string GetName() const;
		unsigned int GetID() const;
		list<Component*> GetComponents();
		Scene* GetScene() const;

		template <class T> T* AddComponent();
		template <class T> T* FetchComponent();
		template <class T> void DeleteComponent();
		void DeleteComponent(Component* component);
	};
}

#include "Entity.inl"
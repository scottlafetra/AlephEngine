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
		bool renderMe;
		bool renderable;

	private:
		string name;

		unsigned int id;
		static unsigned int nextId;
		list<Component*> components;
		Scene* scene;

		// Private to make sure that only a scene can create it
		Entity( string name );

	protected:
		void Error( string errorMessage );
		void FatalError( string errorMessage );

	public:
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
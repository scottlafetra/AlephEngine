#pragma once
#include <vector>
#include <algorithm>
#include "Scene.h"

namespace AlephEngine
{
	// Forward Declarations
	class Component;

	class Entity
	{
		friend class Scene;

	public:
		std::string tag;
		bool renderMe;
		bool renderable;

	private:
		std::string name;

		unsigned int id;
		static unsigned int nextId;
		std::list<Component*> components;
		Scene* scene;

		// Private to make sure that only a scene can create it
		Entity(std::string name );

	protected:
		void Error(std::string errorMessage );
		void FatalError(std::string errorMessage );

	public:
		~Entity();

		std::string GetName() const;
		unsigned int GetID() const;
		std::list<Component*> GetComponents();
		Scene* GetScene() const;

		template <class T> T* AddComponent();
		template <class T> T* FetchComponent();
		template <class T> void DeleteComponent();
		void DeleteComponent(Component* component);
	};
}

#include "Entity.inl"
#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Component.h"

namespace Biendeo::GameOff2016::Engine {
	class Engine;

	class GameObject {
		public:
		static const uint16_t MAXIMUM_CHILD_DEPTH = 1024;

		GameObject(Engine& engine);
		~GameObject();

		// Gets the first component that matches the given type, or null if there isn't one.
		template<class T> std::weak_ptr<T> GetComponent();
		// Gets a vector of all the components that match the given type.
		template<class T> std::vector<std::weak_ptr<T>> GetComponents();
		// Adds this component to the GameObject. This needs to be a raw pointer, it will be
		// managed by this object afterwards.
		bool AddComponent(Component* c);

		// Destroys this object and removes it from the engine.
		void Destroy();

		std::string Name();
		std::string Name(std::string newName);

		uint64_t ID();
		// Do not call this method manually, or the engine will not be able to find the object.
		uint64_t ID(uint64_t newId);

		std::weak_ptr<GameObject> Parent();
		std::weak_ptr<GameObject> Parent(std::weak_ptr<GameObject> newParent);

		std::map<uint64_t, std::weak_ptr<GameObject>> Children();

		std::weak_ptr<GameObject> GetWeakPointer();
		
		// Returns the object's depth in the world hierarchy. It's 0 if it is at the root.
		uint16_t GetChildDepth();

		protected:
		std::string name;
		std::vector<std::shared_ptr<Component>> components;

		std::weak_ptr<GameObject> parent;
		std::map<uint64_t, std::weak_ptr<GameObject>> children;

		Engine* engine;

		uint64_t id;
	};

}
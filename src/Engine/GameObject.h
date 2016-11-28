#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Component.h"
#include "Components/Transform.h"

namespace Biendeo::GameOff2016::Engine {
	class Engine;

	class GameObject {
		public:
		static const uint16_t MAXIMUM_CHILD_DEPTH = 1024;

		GameObject(Engine& engine);
		~GameObject();

		// Gets the first component that matches the given type, or null if there isn't one.
		template<class T> std::weak_ptr<T> GameObject::GetComponent();
		// Gets a vector of all the components that match the given type.
		template<class T> std::vector<std::weak_ptr<T>> GetComponents();
		// Adds this component to the GameObject. This needs to be a raw pointer, it will be
		// managed by this object afterwards.
		bool AddComponent(Component* c);

		// Destroys this object and removes it from the engine.
		void Destroy();

		Components::Transform& Transform();

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

		bool Active();
		bool Active(bool activeState);
		bool ToggleActive();

		// Gets called before Start when the object is created.
		void Awake();
		// Gets called after Update every framew.
		void LateUpdate();
		// Gets called when the object is made active.
		void OnActive();
		// Gets called when the object is destroyed.
		void OnDestroy();
		// Gets called when the object is made inactive.
		void OnDisable();
		// Gets called when the object is created.
		void Start();
		// Gets called every frame.
		void Update();

		protected:
		std::string name;
		std::vector<std::shared_ptr<Component>> components;

		std::weak_ptr<GameObject> parent;
		std::map<uint64_t, std::weak_ptr<GameObject>> children;

		Engine* engine;

		std::weak_ptr<Components::Transform> transform;

		uint64_t id;

		bool active;

		bool initialized;
	};

	template<class T> inline std::weak_ptr<T> GameObject::GetComponent() {
		for (std::shared_ptr<Component>& c : components) {
			if (std::dynamic_pointer_cast<T>(c) != nullptr) {
				return std::weak_ptr<T>(std::dynamic_pointer_cast<T>(c));
			}
		}
		return std::weak_ptr<T>(std::shared_ptr<T>(nullptr));
	};

	template<class T> inline std::vector<std::weak_ptr<T>> GameObject::GetComponents() {
		std::vector<std::weak_ptr<T>> foundComponents;
		for (std::shared_ptr<Component>& c : components) {
			if (std::dynamic_pointer_cast<T>(c) != nullptr) {
				foundComponents.push_back(std::weak_ptr<T>(std::dynamic_pointer_cast<T>(c)));
			}
		}

		return foundComponents;
	}

}
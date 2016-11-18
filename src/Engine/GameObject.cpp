#include "GameObject.h"

#include "Engine.h"

namespace Biendeo::GameOff2016::Engine {

	GameObject::GameObject(Engine& engine) {
		this->engine = &engine;
	}

	GameObject::~GameObject() {

	}

	template<class T> std::weak_ptr<T> GameObject::GetComponent() {
		for (Component& c : components) {
			if (dynamic_cast<T*>(&c) != nullptr) {
				return std::weak_ptr<T>(c);
			}
		}
		return null;
	}

	template<class T> std::vector<std::weak_ptr<T>> GameObject::GetComponents() {
		std::vector<std::weak_ptr<T>> foundComponents;
		for (Component& c : components) {
			if (dynamic_cast<T*>(&c) != nullptr) {
				foundComponents.push_back(std::weak_ptr<T>(c));
			}
		}

		return foundComponents;
	}

	bool GameObject::AddComponent(Component* c) {
		components.push_back(std::shared_ptr<Component>(c));
		return true;
	}

	void GameObject::Destroy() {
		// TODO: Figure out what needs to be done first.
		typedef std::map<uint64_t, std::weak_ptr<GameObject>>::iterator iterator;

		for (iterator it = children.begin(); it != children.end(); it++) {
			//auto s = it->second;
			std::shared_ptr<GameObject> p = std::shared_ptr<GameObject>(it->second);
			p->Destroy();
			//Sleep(1);
		}
		engine->RemoveGameObject(*this);
	}

	std::string GameObject::Name() {
		return name;
	}

	std::string GameObject::Name(std::string newName) {
		this->name = newName;
		return name;
	}

	uint64_t GameObject::ID() {
		return id;
	}

	uint64_t GameObject::ID(uint64_t newId) {
		this->id = newId;
		return id;
	}

	std::weak_ptr<GameObject> GameObject::Parent() {
		return parent;
	}

	std::weak_ptr<GameObject> GameObject::Parent(std::weak_ptr<GameObject> newParent) {
		// TODO: Additional things for unsetting the previous parent such as repositioning, etc.
		std::shared_ptr<GameObject> newParentPtr = std::shared_ptr<GameObject>(newParent);

		if (newParentPtr->GetChildDepth() >= MAXIMUM_CHILD_DEPTH) {
			std::string message = newParentPtr->Name() + " is at the maximum child depth of " + std::to_string(MAXIMUM_CHILD_DEPTH) + ", cannot set parent.";
			throw std::exception(message.data());
		}

		if (!parent.expired()) {
			std::shared_ptr<GameObject> oldParentPtr = std::shared_ptr<GameObject>(parent);
			if (oldParentPtr != nullptr && oldParentPtr->children.find(ID()) != oldParentPtr->children.end()) {
				oldParentPtr->children.erase(ID());
			}
		}

		this->parent = newParent;

		if (newParentPtr != nullptr) {
			newParentPtr->children.insert(std::pair<uint64_t, std::weak_ptr<GameObject>>(ID(), GetWeakPointer()));
		}

		return parent;
	}

	std::map<uint64_t, std::weak_ptr<GameObject>> GameObject::Children() {
		return children;
	}

	std::weak_ptr<GameObject> GameObject::GetWeakPointer() {
		return std::weak_ptr<GameObject>(engine->GetGameObjectWeakPointer(*this));
	}

	uint16_t GameObject::GetChildDepth() {
		if (parent.expired()) {
			return 0;
		}

		auto ptr = std::shared_ptr<GameObject>(parent);
		if (ptr != nullptr) {
			return ptr->GetChildDepth() + 1;
		} else {
			return 0;
		}
	}
}
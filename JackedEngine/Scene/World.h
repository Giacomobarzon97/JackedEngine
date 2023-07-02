#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include "Scene/Components/SceneComponent.h"

class ComponentsIterator {
public:
	ComponentsIterator(std::vector<SceneComponent*>& components);
	SceneComponent* Next();
	const bool HasNext() const;
private:
	std::vector<SceneComponent*>::iterator iterator;
	std::vector<SceneComponent*>::iterator end;
};

class World {
public:
	~World();

	template <typename ComponentType> 
	ComponentType& CreateComponent(std::string name);
	ComponentsIterator GetComponentIterator();

private:
	std::vector<SceneComponent*> components;
};

template <typename ComponentType>
ComponentType& World::CreateComponent(std::string name) {
	for (unsigned int i = 0; i < components.size(); i++) {
		if (name == components[i]->GetName()) {
			throw std::runtime_error("An object with this name already exists");
		}
	}
	ComponentType* component = new ComponentType(name);
	components.push_back(component);
	component->Init();
	return *component;
}
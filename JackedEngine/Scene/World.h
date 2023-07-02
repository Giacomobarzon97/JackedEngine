#pragma once
#include <string>
#include <unordered_map>
#include <stdexcept>
#include "Scene/Components/SceneComponent.h"

class ComponentsIterator {
public:
	ComponentsIterator(std::unordered_map <std::string, SceneComponent*>& map);
	SceneComponent* Next();
	const bool HasNext() const;
private:
	std::unordered_map <std::string, SceneComponent*>::iterator iterator;
	std::unordered_map <std::string, SceneComponent*>::iterator end;
};

class World {
public:
	~World();

	template <typename ComponentType> 
	ComponentType& CreateComponent(std::string name);
	ComponentsIterator GetComponentIterator();

private:
	std::unordered_map<std::string, SceneComponent*> componentsMap;
};

template <typename ComponentType>
ComponentType& World::CreateComponent(std::string name) {
	if (componentsMap.find(name) != componentsMap.end()) {
		throw std::runtime_error("An object already exists with the same name");
	}

	ComponentType* component = new ComponentType();
	componentsMap[name] = component;
	component->Init();
	return *component;
}
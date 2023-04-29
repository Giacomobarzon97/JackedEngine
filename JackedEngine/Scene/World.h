#pragma once
#include <string>
#include <vector>
#include "Scene/Components/SceneComponent.h"

class World {
public:
	~World();

	template <typename ComponentType> 
	ComponentType& CreateComponent();

	const std::vector<SceneComponent*> GetComponents() const;

private:
	std::vector<SceneComponent*> components;
};

template <typename ComponentType>
ComponentType& World::CreateComponent() {
	ComponentType* component = new ComponentType();
	components.push_back(component);
	return *component;
}
#pragma once
#include <string>
#include <vector>
#include "Scene/Components/SceneComponent.h"

class World {
public:
	~World();

	template <typename ComponentType> 
	ComponentType& CreateComponent();

	void Init();

	const std::vector<SceneComponent*> GetComponents() const;

private:
	enum WorldState {
		BEFORE_INIT,
		INIT
	};

	WorldState currentWorldState = BEFORE_INIT;
	std::vector<SceneComponent*> components;
};

template <typename ComponentType>
ComponentType& World::CreateComponent() {
	ComponentType* component = new ComponentType();
	components.push_back(component);

	if (currentWorldState < WorldState::INIT) {
		component->Init();
	}

	return *component;
}
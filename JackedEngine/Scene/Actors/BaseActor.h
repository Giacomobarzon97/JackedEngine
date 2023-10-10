#pragma once
#include <vector>
#include <stdexcept>
#include "Scene/Components/BaseComponent.h"

struct ActorInitializer {
	std::string name;
};

class BaseActor {
public:
	BaseActor(ActorInitializer initializer);
	virtual ~BaseActor();

	virtual void Init();
	virtual void Tick(double deltaTime);

	std::string GetName();

	template <typename ComponentType>
	ComponentType& CreateComponent(std::string name);

private:
	std::vector<BaseComponent*> components;
	std::string name;
};

template <typename ComponentType>
ComponentType& BaseActor::CreateComponent(std::string name) {
	for (unsigned int i = 0; i < components.size(); i++) {
		if (name == components[i]->GetName()) {
			throw std::runtime_error("A component with this name already exists in this actor");
		}
	}
	ComponentInitializer initializer;
	initializer.name = name;
	initializer.actorOwner = this;

	ComponentType* component = new ComponentType(initializer);
	components.push_back(component);
	return *component;
}
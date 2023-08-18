#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include "Scene/Actors/BaseActor.h"

class World {
public:
	~World();

	template <typename ComponentType> 
	ComponentType& CreateActor(std::string name);
	std::vector<BaseActor*> GetActors();

private:
	std::vector<BaseActor*> actors;
};

template <typename ActorType>
ActorType& World::CreateActor(std::string name) {
	for (unsigned int i = 0; i < actors.size(); i++) {
		if (name == actors[i]->GetName()) {
			throw std::runtime_error("An actor with this name already exists");
		}
	}

	ActorInitializer initializer;
	initializer.name = name;
	ActorType* actor = new ActorType(initializer);
	actors.push_back(actor);
	actor->Init();
	return *actor;
}
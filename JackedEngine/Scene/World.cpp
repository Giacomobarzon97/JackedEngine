#include "World.h"

World::~World() {
	for (unsigned int i = 0; i < components.size(); i++) {
		delete components[i];
	}
}

void World::Init() {
	for (unsigned int i = 0; i < components.size(); i++) {
		components[i]->Init();
	}
	currentWorldState = INIT;
}

const std::vector<SceneComponent*> World::GetComponents() const {
	return components;
}

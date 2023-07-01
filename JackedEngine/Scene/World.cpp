#include "World.h"

World::~World() {
	for (unsigned int i = 0; i < components.size(); i++) {
		delete components[i];
	}
}

const std::vector<SceneComponent*> World::GetComponents() const {
	return components;
}

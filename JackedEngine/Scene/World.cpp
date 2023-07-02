#include "World.h"

ComponentsIterator::ComponentsIterator(std::vector<SceneComponent*>& components) :
	iterator(components.begin()),
	end(components.end())
{}

SceneComponent* ComponentsIterator::Next() {
	SceneComponent* component = *iterator;
	iterator++;
	return component;
}

const bool ComponentsIterator::HasNext() const {
	return iterator != end;
}

World::~World() {
	for (auto it = components.begin(); it != components.end(); it++) {
		delete *it;
	}
}

ComponentsIterator World::GetComponentIterator() {
	return ComponentsIterator(components);
}

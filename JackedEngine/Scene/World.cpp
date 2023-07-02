#include "World.h"

ComponentsIterator::ComponentsIterator(std::unordered_map <std::string, SceneComponent*>& map) :
	iterator(map.begin()),
	end(map.end())
{}

SceneComponent* ComponentsIterator::Next() {
	SceneComponent* component = iterator->second;
	iterator++;
	return component;
}

const bool ComponentsIterator::HasNext() const {
	return iterator != end;
}

World::~World() {
	for (auto it = componentsMap.begin(); it != componentsMap.end(); it++) {
		delete it->second;
	}
}

ComponentsIterator World::GetComponentIterator() {
	return ComponentsIterator(componentsMap);
}

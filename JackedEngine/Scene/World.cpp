#include "World.h"

World::~World() {
	for (auto it = actors.begin(); it != actors.end(); it++) {
		delete *it;
	}
}

std::vector<BaseActor*> World::GetActors() {
	return actors;
}

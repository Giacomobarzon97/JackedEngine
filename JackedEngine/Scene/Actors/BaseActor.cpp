#include "BaseActor.h"

BaseActor::BaseActor(ActorInitializer initializer) :
	name(initializer.name)
{

}

BaseActor::~BaseActor() {
	for (auto it = components.begin(); it != components.end(); it++) {
		delete* it;
	}
}

void BaseActor::Init() {
	for (unsigned int i = 0; i < components.size(); i++) {
		components[i]->Init();
	}
}

void BaseActor::Tick(float deltaTime) {
	for (unsigned int i = 0; i < components.size(); i++) {
		components[i]->Tick(deltaTime);
	}
}

std::string BaseActor::GetName() {
	return name;
}
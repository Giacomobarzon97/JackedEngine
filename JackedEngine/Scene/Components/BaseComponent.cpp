#include "BaseComponent.h"

BaseComponent::BaseComponent(ComponentInitializer initializer) :
	name(initializer.name),
	actorOwner(initializer.actorOwner)
{}

BaseComponent::~BaseComponent() {}

const std::string BaseComponent::GetName() {
	return name;
}

BaseActor& BaseComponent::GetActorOwner() {
	return *actorOwner;
}

void BaseComponent::Init() {

}

void BaseComponent::Tick(double deltaTime) {

}
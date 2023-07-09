#include "BaseCameraComponent.h"

BaseCameraComponent::BaseCameraComponent(std::string name) :
	SceneComponent(name)
{}

void BaseCameraComponent::Init() {
	SceneComponent::Init();
}

void BaseCameraComponent::Tick(double deltaTime) {
	SceneComponent::Tick(deltaTime);
}

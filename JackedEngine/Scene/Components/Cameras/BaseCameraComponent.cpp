#include "BaseCameraComponent.h"

BaseCameraComponent::BaseCameraComponent(ComponentInitializer initializer) :
	SceneComponent(initializer)
{}

void BaseCameraComponent::Init() {
	SceneComponent::Init();
}

void BaseCameraComponent::Tick(double deltaTime) {
	SceneComponent::Tick(deltaTime);
}

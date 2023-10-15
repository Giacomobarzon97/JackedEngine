#include "BaseLightComponent.h"

BaseLightComponent::BaseLightComponent(ComponentInitializer initializer) :
	SceneComponent(initializer)
{}

void BaseLightComponent::Init() {
	SceneComponent::Init();
}

void BaseLightComponent::Tick(double deltaTime) {
	SceneComponent::Tick(deltaTime);
}

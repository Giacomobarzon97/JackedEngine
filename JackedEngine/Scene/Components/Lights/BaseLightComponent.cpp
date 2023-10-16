#include "BaseLightComponent.h"

BaseLightComponent::BaseLightComponent(ComponentInitializer initializer) :
	SceneComponent(initializer)
{}

void BaseLightComponent::Init() {
	SceneComponent::Init();
	lightReference = JackedEngine::GetRenderer().CreateLight();
}

void BaseLightComponent::Tick(double deltaTime) {
	SceneComponent::Tick(deltaTime);
}

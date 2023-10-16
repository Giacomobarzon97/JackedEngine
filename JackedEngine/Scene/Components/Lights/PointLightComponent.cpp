#include  "PointLightComponent.h"

PointLightComponent::PointLightComponent(ComponentInitializer initializer) :
	BaseLightComponent(initializer)
{}

void PointLightComponent::Init() {
	BaseLightComponent::Init();
}

void PointLightComponent::Tick(double deltaTime) {
	BaseLightComponent::Tick(deltaTime);
	lightReference.SetPosition({ GetPosition(), 1 });
}
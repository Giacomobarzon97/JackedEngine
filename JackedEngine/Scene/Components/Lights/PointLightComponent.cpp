#include  "PointLightComponent.h"

PointLightComponent::PointLightComponent(ComponentInitializer initializer) :
	BaseLightComponent(initializer)
{}

void PointLightComponent::Init() {
	BaseLightComponent::Init();
	lightReference.SetLightColor({ 1,1,1 });
	lightReference.SetRadius(5);
}

void PointLightComponent::Tick(double deltaTime) {
	BaseLightComponent::Tick(deltaTime);
	lightReference.SetPosition({ GetPosition(), 1 });
}
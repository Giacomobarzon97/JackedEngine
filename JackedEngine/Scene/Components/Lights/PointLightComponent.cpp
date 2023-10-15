#include  "PointLightComponent.h"

PointLightComponent::PointLightComponent(ComponentInitializer initializer) :
	BaseLightComponent(initializer)
{}

void PointLightComponent::Init() {
	BaseLightComponent::Init();
	pointLightReference = JackedEngine::GetRenderer().CreatePointLight();
}

void PointLightComponent::Tick(double deltaTime) {
	BaseLightComponent::Tick(deltaTime);
	pointLightReference.UpdatePosition(GetPosition());
}
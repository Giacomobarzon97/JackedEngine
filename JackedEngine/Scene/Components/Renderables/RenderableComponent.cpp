#include "RenderableComponent.h"

RenderableComponent::RenderableComponent(ComponentInitializer initializer) :
	SceneComponent(initializer)
{}

void RenderableComponent::Init() {
	SceneComponent::Init();
}

void RenderableComponent::Tick(double deltaTime) {
	SceneComponent::Tick(deltaTime);
}
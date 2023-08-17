#include "RenderableComponent.h"

RenderableComponent::RenderableComponent(std::string name) :
	SceneComponent(name)
{}

void RenderableComponent::Init() {
	SceneComponent::Init();
}

void RenderableComponent::Tick(double deltaTime) {
	SceneComponent::Tick(deltaTime);
}
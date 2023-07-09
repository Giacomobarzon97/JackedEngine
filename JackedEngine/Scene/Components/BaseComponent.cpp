#include "BaseComponent.h"

BaseComponent::BaseComponent(std::string name) :
	name(name)
{}

BaseComponent::~BaseComponent() {}

const std::string BaseComponent::GetName() {
	return name;
}

void BaseComponent::Init() {

}

void BaseComponent::Tick(double deltaTime) {

}
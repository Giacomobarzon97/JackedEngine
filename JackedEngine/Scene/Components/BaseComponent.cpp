#include "BaseComponent.h"

BaseComponent::BaseComponent(const std::string name) :
	name(name)
{}

BaseComponent::~BaseComponent() {}

const std::string BaseComponent::GetName() const{
	return name;
}
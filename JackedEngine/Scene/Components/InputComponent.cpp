#include "InputComponent.h"

InputComponent::InputComponent(ComponentInitializer initializer) :
	BaseComponent(initializer)
{}

void InputComponent::BindKey(BindableKey key, std::function<void()> binding) {
	JackedEngine::GetWindow().BindKey(key, binding);
}
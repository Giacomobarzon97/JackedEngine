#include "InputComponent.h"

InputComponent::InputComponent(ComponentInitializer initializer) :
	BaseComponent(initializer)
{
	JackedEngine::GetWindow().BindCallback(std::bind(
		&InputComponent::OnInputReceived, 
		this, 
		std::placeholders::_1, 
		std::placeholders::_2
	));
}

void InputComponent::Tick(double deltaTime) {
	for (InputKey activeKey : activeKeys) {
		for (auto functionBiding : functionBindings[activeKey]) {
			functionBiding();
		}
	}
}

void InputComponent::OnInputReceived(InputKey key, InputEvent event) {
	if (event == START) {
		activeKeys.insert(key);
	}
	if (event == END) {
		activeKeys.erase(activeKeys.find(key));
	}
}

void InputComponent::BindAction(InputKey key, std::function<void()> binding) {
	if (functionBindings.find(key) == functionBindings.end()) {
		functionBindings[key] = std::vector<std::function<void()>>();
	}
	functionBindings[key].push_back(binding);
}
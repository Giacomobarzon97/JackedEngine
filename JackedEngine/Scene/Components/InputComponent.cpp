#include "InputComponent.h"

InputComponent::InputComponent(ComponentInitializer initializer) :
	BaseComponent(initializer)
{
	JackedEngine::GetInputManager().BindCallback(std::bind(
		&InputComponent::OnInputReceived, 
		this, 
		std::placeholders::_1, 
		std::placeholders::_2,
		std::placeholders::_3
	));
}

void InputComponent::Tick(double deltaTime) {
	for (InputKey activeKey : activeKeys) {
		for (auto actionBinding : actionBindings[activeKey]) {
			actionBinding();
		}
		for (auto axisBinding : axisBindings[activeKey]) {
			axisBinding.binding(axisBinding.axisScaleValue * axisBinding.tickScaleValue * deltaTime);
		}
	}
}

void InputComponent::OnInputReceived(InputKey key, InputEvent event, float scaleValue) {
	if (event == START) {
		activeKeys.insert(key);
	}
	if (event == START || event == REPEAT) {
		for (AxisMapping mapping : axisBindings[key]) {
			mapping.tickScaleValue = scaleValue;
		}
	}
	if (event == END) {
		activeKeys.erase(activeKeys.find(key));
	}
}

void InputComponent::BindAction(InputKey key, std::function<void()> binding) {
	if (actionBindings.find(key) == actionBindings.end()) {
		actionBindings[key] = std::vector<std::function<void()>>();
	}
	actionBindings[key].push_back(binding);
}

void InputComponent::BindAxis(std::string id, std::function<void(float)> binding) {
	std::vector<std::tuple<InputKey, float>> keyMappings = JackedEngine::GetInputManager().GetAxisData(id);
	for (std::tuple<InputKey, float> keyMapping : keyMappings) {
		AxisMapping mapping;
		mapping.binding = binding;
		mapping.axisScaleValue = std::get<1>(keyMapping);
		mapping.tickScaleValue = 1.0f;
		axisBindings[std::get<0>(keyMapping)].push_back(mapping);
	}
}
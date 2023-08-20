#pragma once
#include <set>
#include "JackedEngine.h"
#include "Scene/Components/BaseComponent.h"
#include "Input/InputConstants.h"

class InputComponent : public BaseComponent{
public:
	InputComponent(ComponentInitializer initializer);

	virtual void Tick(double deltaTime) override;

	void OnInputReceived(InputKey key, InputEvent event, float scaleValue);
	void BindAction(InputKey key, std::function<void()> binding);
	void BindAxis(std::string id, std::function<void(float)> binding);

private:
	struct AxisMapping {
		std::function<void(float)> binding;
		float axisScaleValue;
		float tickScaleValue;
	};

	std::unordered_map<InputKey, std::vector<std::function<void()>>> actionBindings;
	std::unordered_map<InputKey, std::vector<AxisMapping>> axisBindings;
	std::set<InputKey> activeKeys;
	std::set<InputKey> keysToRemoveEndTick;
};
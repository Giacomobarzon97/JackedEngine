#pragma once
#include <set>
#include "JackedEngine.h"
#include "Scene/Components/BaseComponent.h"

class InputComponent : public BaseComponent{
public:
	InputComponent(ComponentInitializer initializer);

	virtual void Tick(double deltaTime) override;

	void OnInputReceived(InputKey key, InputEvent event);
	void BindAction(InputKey key, std::function<void()> binding);

private:
	std::unordered_map<InputKey, std::vector<std::function<void()>>> functionBindings;
	std::set<InputKey> activeKeys;
};
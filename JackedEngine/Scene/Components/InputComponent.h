#pragma once
#include "JackedEngine.h"
#include "Scene/Components/BaseComponent.h"

class InputComponent : public BaseComponent{
public:
	InputComponent(ComponentInitializer initializer);

	void BindKey(BindableKey key, std::function<void()> binding);
};
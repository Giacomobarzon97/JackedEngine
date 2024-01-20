#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include "Scene/Components/SceneComponent.h"

class RenderableComponent : public SceneComponent {
public:
	RenderableComponent(ComponentInitializer initializer);

	virtual void Init();
	virtual void Tick(double deltaTime);
};
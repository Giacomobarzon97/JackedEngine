#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include "Scene/Components/SceneComponent.h"

class RenderableComponent : public SceneComponent {
public:
	RenderableComponent(const std::string name);

	virtual void Draw() = 0;
};
#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include "Scene/Components/SceneComponent.h"

class RenderableComponent : public SceneComponent {
public:
	virtual void Draw() const = 0;
	virtual const glm::mat4 GetModelMatrix() const = 0;
};
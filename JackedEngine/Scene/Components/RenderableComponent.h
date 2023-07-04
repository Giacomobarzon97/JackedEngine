#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include "Scene/Components/SceneComponent.h"
#include "Scene/Materials/BaseMaterial.h"

class RenderableComponent : public SceneComponent {
public:
	RenderableComponent(std::string name);
};
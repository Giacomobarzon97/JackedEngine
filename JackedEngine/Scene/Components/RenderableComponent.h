#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include "Scene/Components/SceneComponent.h"
#include "Scene/Materials/BaseMaterial.h"

class RenderableComponent : public SceneComponent {
public:
	//TODO: Substitute theese getter methods with a draw method (Need to create renderer class first)
	virtual const ShaderType GetShaderType() const = 0;
	virtual const ModelReference GetModel() const = 0;
	virtual const BaseMaterial& GetMaterial() const = 0;
	virtual const glm::mat4 GetModelMatrix() const = 0;
};
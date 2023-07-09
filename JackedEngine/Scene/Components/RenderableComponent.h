#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include "Scene/Components/SceneComponent.h"

class RenderableComponent : public SceneComponent {
public:
	RenderableComponent(std::string name);

	virtual void Init();
	virtual void Tick(double deltaTime);

protected:
	glm::mat4 modelMatrix;

private:
	void applyTranslation();
	void applyRotation();
	void applyScale();
};
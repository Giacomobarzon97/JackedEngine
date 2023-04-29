#pragma once
#include "Scene/Components/SceneComponent.h"

class BaseCameraComponent : public SceneComponent {
public:
	virtual const glm::mat4 GetViewMatrix() const = 0;
	virtual const glm::mat4 GetProjectionMatrix(const uint32_t width, const uint32_t height) const = 0;
};
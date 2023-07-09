#pragma once
#include "Scene/Components/SceneComponent.h"

class BaseCameraComponent : public SceneComponent {
public:
	BaseCameraComponent(std::string name);

	virtual void Init() override;
	virtual void Tick(double deltaTime) override;

	virtual void UpdateCameraStatus() = 0;
	virtual const glm::mat4 GetViewMatrix() const = 0;
	virtual const glm::mat4 GetProjectionMatrix(const uint32_t width, const uint32_t height) const = 0;
};
#pragma once
#include "Scene/Components/SceneComponent.h"

class BaseCameraComponent : public SceneComponent {
public:
	BaseCameraComponent(ComponentInitializer initializer);

	virtual void Init() override;
	virtual void Tick(double deltaTime) override;

	virtual const glm::mat4 GetViewMatrix() const = 0;
	virtual const glm::mat4 GetProjectionMatrix(const uint32_t width, const uint32_t height) const = 0;
	virtual const glm::vec3 getXAxis() const = 0;
	virtual const glm::vec3 getYAxis() const = 0;
	virtual const glm::vec3 getZAxis() const = 0;
};
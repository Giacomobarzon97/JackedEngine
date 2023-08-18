#pragma once
#define _USE_MATH_DEFINES
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene/Components/Cameras/BaseCameraComponent.h"

class PerspectiveCamera : public BaseCameraComponent
{
public:
	PerspectiveCamera(ComponentInitializer initializer);

	virtual void Init() override;
	virtual void Tick(double deltaTime) override;

	virtual const glm::mat4 GetViewMatrix() const override;
	virtual const glm::mat4 GetProjectionMatrix(const uint32_t width, const uint32_t height) const override;

private:
	double drawDistance = 2;
	static void rotAxes(glm::vec3& axis_a, glm::vec3& axis_b, double angle);
};
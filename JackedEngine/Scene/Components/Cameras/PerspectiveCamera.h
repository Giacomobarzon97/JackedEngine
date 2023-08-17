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
	PerspectiveCamera(std::string name);

	virtual void Init() override;
	virtual void Tick(double deltaTime) override;

	virtual const glm::mat4 GetViewMatrix() const override;
	virtual const glm::mat4 GetProjectionMatrix(const uint32_t width, const uint32_t height) const override;

private:
	double drawDistance = 2;
};
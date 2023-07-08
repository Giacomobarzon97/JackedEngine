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
	virtual void Tick() override;

	virtual void UpdateCameraStatus() override;
	virtual const glm::mat4 GetViewMatrix() const override;
	virtual const glm::mat4 GetProjectionMatrix(const uint32_t width, const uint32_t height) const override;

private:
	glm::vec3 upVector = glm::vec3(0.0f,0.0f,1.0f);
	double drawDistance = 2;

	glm::vec3 eye;
	glm::vec3 center;

	void updateTranslation();
	void updateRotation();
};
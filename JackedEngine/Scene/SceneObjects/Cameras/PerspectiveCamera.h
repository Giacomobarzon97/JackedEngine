#pragma once
#define _USE_MATH_DEFINES
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene/SceneObjects/Cameras/BaseCameraObject.h"
#include "Windows/BaseWindow.h"

class PerspectiveCamera : public BaseCameraObject
{
public:
	PerspectiveCamera(const std::string name, const BaseWindow& window, const glm::vec3 position, const glm::vec3 direction);

	virtual void Rotate(const double x, const double y, const double z) override;
	virtual void Translate(const double x, const double y, const double z) override;
	virtual void SetPosition(const double x, const double y, const double z) override;
	virtual void SetRotation(const double x, const double y, const double z) override;

	virtual const glm::mat4 GetViewMatrix() const override;
	virtual const glm::mat4 GetProjectionMatrix() const override;

private:
	const BaseWindow& window;

	glm::vec3 upVector = glm::vec3(0.0f,0.0f,1.0f);
	double drawDistance = 2;

	glm::vec3 eye;
	glm::vec3 center;

	double currentXangle = 0, currentYangle = 0, currentZangle = 0;
};
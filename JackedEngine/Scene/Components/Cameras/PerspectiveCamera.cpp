#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(std::string name) :
	BaseCameraComponent(name)
{}

void PerspectiveCamera::Init() {
	BaseCameraComponent::Init();
	eye = {2,2,2};
	center = glm::vec3({ 2,2,2 }) + (glm::vec3({-2,-2,-2}) / glm::length(glm::vec3({ -2,-2,-2 })));
}

void PerspectiveCamera::Tick(double deltaTime) {
	BaseCameraComponent::Tick(deltaTime);
}

void PerspectiveCamera::UpdateCameraStatus() {
	eye = { 2,2,2 };
	center = glm::vec3({ 2,2,2 }) + (glm::vec3({ -2,-2,-2 }) / glm::length(glm::vec3({ -2,-2,-2 })));

	updateTranslation();
	updateRotation();
}

const glm::mat4 PerspectiveCamera::GetViewMatrix() const {
	return glm::lookAt(eye, center, upVector);
}

const glm::mat4 PerspectiveCamera::GetProjectionMatrix(const uint32_t width, const uint32_t height) const {
	glm::mat4 proj = glm::perspective(glm::radians(90.0f), width / (float)height, 0.1f, 10.0f);
	proj[1][1] *= -1;
	return proj;
}

void PerspectiveCamera::updateTranslation() {
	glm::vec3 transVec = { xTrans, yTrans, zTrans };
	eye = eye + transVec;
	center = center + transVec;
}

void PerspectiveCamera::updateRotation() {
	double radAngle;
	glm::mat3 rotMat;

	radAngle = pitch * M_PI / 180;
	center = center + eye;
	rotMat = {
		{1,0,0},
		{0, cos(radAngle), -sin(radAngle)},
		{0, sin(radAngle), cos(radAngle)}
	};
	center = rotMat * center;
	center = center - eye;

	radAngle = yaw * M_PI / 180;
	center = center + eye;
	rotMat = {
		{cos(radAngle),0,sin(radAngle)},
		{0, 1, 0},
		{-sin(radAngle), 0, cos(radAngle)}
	};
	center = rotMat * center;
	center = center - eye;

	radAngle = roll * M_PI / 180;
	center = center + eye;
	rotMat = {
		{cos(radAngle), -sin(radAngle), 0},
		{sin(radAngle), cos(radAngle), 0},
		{0, 0, 1}
	};
	center = rotMat * center;
	center = center - eye;
}
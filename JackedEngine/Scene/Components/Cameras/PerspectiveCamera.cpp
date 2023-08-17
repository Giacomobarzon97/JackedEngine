#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(std::string name) :
	BaseCameraComponent(name)
{}

void PerspectiveCamera::Init() {
	BaseCameraComponent::Init();
	Translate(2, 1, 2);
}

void PerspectiveCamera::Tick(double deltaTime) {
	BaseCameraComponent::Tick(deltaTime);
}

const glm::mat4 PerspectiveCamera::GetViewMatrix() const {
	return glm::inverse(rotationMatrix * translationMatrix);
}

const glm::mat4 PerspectiveCamera::GetProjectionMatrix(const uint32_t width, const uint32_t height) const {
	glm::mat4 proj = glm::perspective(glm::radians(90.0f), width / (float)height, 0.1f, 10.0f);
	proj[1][1] *= -1;
	return proj;
}
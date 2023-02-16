#include "PerspectiveCamera.h"


PerspectiveCamera::PerspectiveCamera(BaseWindow& window) :
	window(window)
{
	eye = glm::vec3(2, 2, 2);
	center = glm::vec3(0, 0,0);
}

void PerspectiveCamera::Rotate(float x, float y, float z) {

}

void PerspectiveCamera::Translate(float x, float y, float z) {

}

void PerspectiveCamera::SetPosition(float x, float y, float z) {

}
void PerspectiveCamera::SetRotation(float x, float y, float z) {

}

glm::mat4 PerspectiveCamera::GetViewProjectionMatrix() const{
	glm::mat4 view = glm::lookAt(eye, center, upVector);
	int width, height;
	window.GetFrameBufferSize(&width, &height);
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), width / (float)height, 0.1f, 10.0f);
	proj[1][1] *= -1;
	return proj*view;
}

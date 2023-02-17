#include "PerspectiveCamera.h"


PerspectiveCamera::PerspectiveCamera(BaseWindow& window) :
	window(window)
{
	eye = {2, 2, 2};
	center = {0, 0, 0};
}

void PerspectiveCamera::Rotate(float x, float y, float z) {
	if (x != 0) {
		float radAngle = x * M_PI / 180;
		center = center + eye;
		glm::mat3 rotMat = {
			{1,0,0},
			{0, cos(radAngle), -sin(radAngle)},
			{0, sin(radAngle), cos(radAngle)}
		};
		center = rotMat * center;
		center = center - eye;
	}
	if (y != 0) {
		float radAngle = y * M_PI / 180;
		center = center + eye;
		glm::mat3 rotMat = {
			{cos(radAngle),0,sin(radAngle)},
			{0, 1, 0},
			{-sin(radAngle), 0, cos(radAngle)}
		};
		center = rotMat * center;
		center = center - eye;
	}
	if (z != 0) {
		float radAngle = z * M_PI / 180;
		center = center + eye;
		glm::mat3 rotMat = {
			{cos(radAngle), -sin(radAngle), 0},
			{sin(radAngle), cos(radAngle), 0},
			{0, 0, 1}
		};
		center = rotMat * center;
		center = center - eye;
	}
}

void PerspectiveCamera::Translate(float x, float y, float z) {
	glm::vec3 transVec = { x, y, z };
	eye = eye + transVec;
	center = center + transVec;
}

void PerspectiveCamera::SetPosition(float x, float y, float z) {
	glm::vec3 direction = center - eye;
	direction = direction / glm::length(direction);
	eye = { x,y,z };
	center = eye + direction;
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

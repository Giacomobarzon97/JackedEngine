#include "PerspectiveCamera.h"


PerspectiveCamera::PerspectiveCamera(const std::string name, const BaseWindow& window, const glm::vec3 position, const glm::vec3 direction) :
	BaseCameraObject(name),
	window(window)
{
	eye = position;
	center = position + (direction/glm::length(direction));
}

void PerspectiveCamera::Rotate(const double x, const double y, const double z) {
	currentXangle += x;
	currentYangle += y;
	currentZangle += z;

	if (x != 0) {
		double radAngle = x * M_PI / 180;
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
		double radAngle = y * M_PI / 180;
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
		double radAngle = z * M_PI / 180;
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

void PerspectiveCamera::Translate(const double x, const double y, const double z) {
	glm::vec3 transVec = { x, y, z };
	eye = eye + transVec;
	center = center + transVec;
}

void PerspectiveCamera::SetPosition(const double x, const double y, const double z) {
	glm::vec3 direction = center - eye;
	direction = direction / glm::length(direction);
	eye = { x,y,z };
	center = eye + direction;
}
void PerspectiveCamera::SetRotation(const double x, const double y, const double z) {
	double xRad = (x * M_PI / 180);
	double yRad = (y * M_PI / 180);
	double zRad = (z * M_PI / 180);

	Rotate(x-currentXangle,y-currentYangle,z-currentZangle);
	currentXangle = xRad;
	currentYangle = yRad;
	currentZangle = zRad;
}

const glm::mat4 PerspectiveCamera::GetViewProjectionMatrix() const{
	glm::mat4 view = glm::lookAt(eye, center, upVector);
	int width, height;
	window.GetFrameBufferSize(&width, &height);
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), width / (float)height, 0.1f, 10.0f);
	proj[1][1] *= -1;
	return proj*view;
}

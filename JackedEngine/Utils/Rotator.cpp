#include "Rotator.h"

Rotator::Rotator() :
	axis({0,0,0})
{}

Rotator::Rotator(glm::vec3 axis) :
	axis({glm::radians(axis.x), glm::radians(axis.y), glm::radians(axis.z)})
{}

glm::vec3 Rotator::GetRotation() const {
	return axis;
}

void Rotator::SetRotation(glm::vec3 axis) {
	this->axis = {glm::radians(axis.x), glm::radians(axis.y), glm::radians(axis.z)};
}

glm::mat4 Rotator::GetRotationMatrix() {
	glm::mat4 tmpRotMat;
	glm::mat4 rotMat(1);

	tmpRotMat = {
		{1,0,0,0},
		{0, cos(axis.x), -sin(axis.x),0},
		{0, sin(axis.x), cos(axis.x),0},
		{0,0,0,1},
	};
	rotMat = rotMat * tmpRotMat;

	tmpRotMat = {
		{cos(axis.y),0,sin(axis.y),0},
		{0, 1, 0,0},
		{-sin(axis.y), 0, cos(axis.y),0},
		{0,0,0,1}
	};
	rotMat = rotMat * tmpRotMat;

	tmpRotMat = {
		{cos(axis.z), -sin(axis.z), 0,0},
		{sin(axis.z), cos(axis.z), 0,0},
		{0, 0, 1,0},
		{0,0,0,1}
	};
	rotMat = rotMat * tmpRotMat;

	return rotMat;
}
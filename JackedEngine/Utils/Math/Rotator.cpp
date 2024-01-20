#include "Rotator.h"

Rotator::Rotator() :
	rotation({0,0,0})
{}

Rotator::Rotator(glm::vec3 rotation) :
	rotation({glm::radians(rotation.x), glm::radians(rotation.y), glm::radians(rotation.z)})
{}

glm::vec3 Rotator::GetRotation() const {
	return rotation;
}

void Rotator::SetRotation(glm::vec3 rotation) {
	this->rotation = {glm::radians(rotation.x), glm::radians(rotation.y), glm::radians(rotation.z)};
}

void Rotator::SetPitch(float value) {
	rotation.x = value;
}

void Rotator::SetYaw(float value) {
	rotation.y = value;
}

void Rotator::SetRoll(float value) {
	rotation.z = value;
}

float Rotator::GetPitch() {
	return rotation.x;
}

float Rotator::GetYaw() {
	return rotation.y;
}

float Rotator::GetRoll() {
	return rotation.z;
}

glm::mat4 Rotator::GetRotationMatrix() {
	glm::mat4 tmpRotMat;
	glm::mat4 rotMat(1);

	tmpRotMat = {
		{1,0,0,0},
		{0, cos(rotation.x), -sin(rotation.x),0},
		{0, sin(rotation.x), cos(rotation.x),0},
		{0,0,0,1},
	};
	rotMat = rotMat * tmpRotMat;

	tmpRotMat = {
		{cos(rotation.y),0,sin(rotation.y),0},
		{0, 1, 0,0},
		{-sin(rotation.y), 0, cos(rotation.y),0},
		{0,0,0,1}
	};
	rotMat = rotMat * tmpRotMat;

	tmpRotMat = {
		{cos(rotation.z), -sin(rotation.z), 0,0},
		{sin(rotation.z), cos(rotation.z), 0,0},
		{0, 0, 1,0},
		{0,0,0,1}
	};
	rotMat = rotMat * tmpRotMat;

	return rotMat;
}
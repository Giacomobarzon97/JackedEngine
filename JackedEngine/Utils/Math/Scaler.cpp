#include "Scaler.h"

Scaler::Scaler() :
	scale({0,0,0})
{}

Scaler::Scaler(glm::vec3 scale) :
	scale(scale)
{}

glm::vec3 Scaler::GetScale() const {
	return scale;
}

void Scaler::SetScale(glm::vec3 scale) {
	this->scale = scale;
}

glm::mat4 Scaler::GetScaleMatrix() {
	glm::mat4 transMat{
		{scale.x, 0, 0, 0},
		{0, scale.y, 0, 0},
		{0, 0, scale.z, 0},
		{0, 0, 0, 1}
	};

	return transMat;
}
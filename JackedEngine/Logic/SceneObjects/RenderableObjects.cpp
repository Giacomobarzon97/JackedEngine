#include "RenderableObject.h"

RenderableObject::RenderableObject(const Model& model) :
	model(model)
{}

void RenderableObject::Rotate(const double x, const double y, const double z) {
	if (x != 0) {
		double radAngle = x * M_PI / 180;
		glm::mat4 rotMat = {
			{1,0,0,0},
			{0, cos(radAngle), -sin(radAngle),0},
			{0, sin(radAngle), cos(radAngle),0},
			{0,0,0,1},
		};
		modelMatrix = modelMatrix * rotMat;
	}
	if (y != 0) {
		double radAngle = y * M_PI / 180;
		glm::mat4 rotMat = {
			{cos(radAngle),0,sin(radAngle),0},
			{0, 1, 0,0},
			{-sin(radAngle), 0, cos(radAngle),0},
			{0,0,0,1}
		};
		modelMatrix = modelMatrix * rotMat;
	}
	if (z != 0) {
		double radAngle = z * M_PI / 180;
		glm::mat4 rotMat = {
			{cos(radAngle), -sin(radAngle), 0,0},
			{sin(radAngle), cos(radAngle), 0,0},
			{0, 0, 1,0},
			{0,0,0,1}
		};
		modelMatrix = modelMatrix * rotMat;
	}
}

void RenderableObject::Translate(const double x, const double y, const double z) {

}

void RenderableObject::Scale(const double x, const double y, const double z) {

}

void RenderableObject::SetPosition(const double x, const double y, const double z) {

}

void RenderableObject::SetRotation(const double x, const double y, const double z) {

}

void RenderableObject::SetScale(const double x, const double y, const double z) {

}

const glm::mat4 RenderableObject::GetModelMatrix() const {
	return modelMatrix;
}

const Model& RenderableObject::GetModel() const {
	return model;
}

void RenderableObject::SetTexture(const std::string texturePath) {
	this->texturePath = texturePath;
}

const std::optional<std::string> RenderableObject::GetTexture() const {
	return texturePath;
}
#include "RenderableObject.h"

RenderableObject::RenderableObject(const std::string name, const std::string modelPath, const std::string texturePath) :
	BaseSceneObject(name),
	modelPath(modelPath),
	texturePath(texturePath)
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

const std::string RenderableObject::GetModelPath() const {
	return modelPath;
}

const std::string RenderableObject::GetTexturePath() const {
	return texturePath;
}
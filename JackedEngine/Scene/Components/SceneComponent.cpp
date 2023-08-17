#include "SceneComponent.h"

SceneComponent::SceneComponent(std::string name) :
	BaseComponent(name),
	translationMatrix(1),
	rotationMatrix(1),
	scaleMatrix(1)
{
	xTrans = yTrans = zTrans = 0;
	pitch = yaw = roll = 0;
	xScale = yScale = zScale = 0;
}

void SceneComponent::Init() {
	BaseComponent::Init();
}

void SceneComponent::Tick(double deltaTime) {
	BaseComponent::Tick(deltaTime);
}

void SceneComponent::Translate(const double x, const double y, const double z) {
	xTrans += x;
	yTrans += y;
	zTrans += z;

	applyTranslation(x, y, z);
}

void SceneComponent::Rotate(const double x, const double y, const double z) {
	float xRad = glm::radians(x);
	float yRad = glm::radians(y);
	float zRad = glm::radians(z);

	pitch += xRad;
	yaw += yRad;
	roll += zRad;

	applyRotation(xRad, yRad, zRad);
}

void SceneComponent::Scale(const double x, const double y, const double z) {
	xScale += x;
	yScale += y;
	zScale += z;

	applyScale(x, y, z);
}

void SceneComponent::SetPosition(const double x, const double y, const double z) {
	applyTranslation(x - xTrans, y - yTrans, z - zTrans);

	xTrans = x;
	yTrans = y;
	zTrans = z;
}

void SceneComponent::SetRotation(const double x, const double y, const double z) {
	float xRad = glm::radians(x);
	float yRad = glm::radians(y);
	float zRad = glm::radians(z);

	applyRotation(xRad - pitch, yRad - yaw, zRad - roll);

	pitch = xRad;
	yaw = yRad;
	roll = zRad;
}

void SceneComponent::SetScale(const double x, const double y, const double z) {
	applyScale(x - xScale, y - yScale, z - zScale);

	xScale = x;
	yScale = y;
	zScale = z;
}


void SceneComponent::applyTranslation(double x, double y, double z) {
	glm::mat4 transMat{
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{xTrans, yTrans, zTrans, 1}
	};

	translationMatrix = translationMatrix * transMat;
}

void SceneComponent::applyRotation(double x, double y, double z) {
	glm::mat4 rotMat;

	rotMat = {
		{1,0,0,0},
		{0, cos(pitch), -sin(pitch),0},
		{0, sin(pitch), cos(pitch),0},
		{0,0,0,1},
	};
	rotationMatrix = rotationMatrix * rotMat;

	rotMat = {
		{cos(yaw),0,sin(yaw),0},
		{0, 1, 0,0},
		{-sin(yaw), 0, cos(yaw),0},
		{0,0,0,1}
	};
	rotationMatrix = rotationMatrix * rotMat;

	rotMat = {
		{cos(roll), -sin(roll), 0,0},
		{sin(roll), cos(roll), 0,0},
		{0, 0, 1,0},
		{0,0,0,1}
	};
	rotationMatrix = rotationMatrix * rotMat;
}

void SceneComponent::applyScale(double x, double y, double z) {

}
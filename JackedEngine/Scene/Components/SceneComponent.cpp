#include "SceneComponent.h"

SceneComponent::SceneComponent(std::string name) :
	BaseComponent(name)
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

	translationMatrix = glm::mat4(1);
	rotationMatrix = glm::mat4(1);
	scaleMatrix = glm::mat4(1);

	applyTranslation();
	applyRotation();
	applyScale();
}

void SceneComponent::Translate(const double x, const double y, const double z) {
	xTrans += x;
	yTrans += y;
	zTrans += z;
}

void SceneComponent::Rotate(const double x, const double y, const double z) {
	pitch += x;
	yaw += y;
	roll += z;
}

void SceneComponent::Scale(const double x, const double y, const double z) {
	xScale += x;
	yScale += y;
	zScale += z;
}

void SceneComponent::SetPosition(const double x, const double y, const double z) {
	xTrans = x;
	yTrans = y;
	zTrans = z;
}

void SceneComponent::SetRotation(const double x, const double y, const double z) {
	pitch = x;
	yaw = y;
	roll = z;
}

void SceneComponent::SetScale(const double x, const double y, const double z) {
	xScale = x;
	yScale = y;
	zScale = z;
}


void SceneComponent::applyTranslation() {
	glm::mat4 transMat{
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{xTrans, yTrans, zTrans, 1}
	};

	translationMatrix = translationMatrix * transMat;
}

void SceneComponent::applyRotation() {
	double radAngle;
	glm::mat4 rotMat;

	radAngle = pitch * M_PI / 180;
	rotMat = {
		{1,0,0,0},
		{0, cos(radAngle), -sin(radAngle),0},
		{0, sin(radAngle), cos(radAngle),0},
		{0,0,0,1},
	};
	rotationMatrix = rotationMatrix * rotMat;

	radAngle = yaw * M_PI / 180;
	rotMat = {
		{cos(radAngle),0,sin(radAngle),0},
		{0, 1, 0,0},
		{-sin(radAngle), 0, cos(radAngle),0},
		{0,0,0,1}
	};
	rotationMatrix = rotationMatrix * rotMat;

	radAngle = roll * M_PI / 180;
	rotMat = {
		{cos(radAngle), -sin(radAngle), 0,0},
		{sin(radAngle), cos(radAngle), 0,0},
		{0, 0, 1,0},
		{0,0,0,1}
	};
	rotationMatrix = rotationMatrix * rotMat;
}

void SceneComponent::applyScale() {

}
#include "SceneComponent.h"

SceneComponent::SceneComponent(ComponentInitializer initializer) :
	BaseComponent(initializer),
	translationMatrix(1),
	rotationMatrix(1),
	scaleMatrix(1),
	currentRotation({0,0,0})
{
	xTrans = yTrans = zTrans = 0;
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

void SceneComponent::Rotate(glm::vec3 rotation) {
	Rotator rotator(rotation);
	rotationMatrix *= rotator.GetRotationMatrix();
	currentRotation += rotation;
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

void SceneComponent::SetRotation(glm::vec3 rotation) {
	glm::vec3 newRotation = rotation - currentRotation;
	Rotator rotator(newRotation);
	rotationMatrix *= rotator.GetRotationMatrix();
	currentRotation = rotation;
}

void SceneComponent::SetScale(const double x, const double y, const double z) {
	applyScale(x - xScale, y - yScale, z - zScale);

	xScale = x;
	yScale = y;
	zScale = z;
}

glm::vec3 SceneComponent::GetRotation() const {
	return currentRotation;
}

glm::vec3 SceneComponent::GetTranslation() const {
	return glm::vec3({ xTrans, yTrans, zTrans });
}


void SceneComponent::applyTranslation(double x, double y, double z) {
	glm::mat4 transMat{
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{x, y, z, 1}
	};

	translationMatrix = translationMatrix * transMat;
}

void SceneComponent::applyScale(double x, double y, double z) {

}
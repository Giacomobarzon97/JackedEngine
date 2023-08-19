#include "SceneComponent.h"

SceneComponent::SceneComponent(ComponentInitializer initializer) :
	BaseComponent(initializer),
	translationMatrix(1),
	rotationMatrix(1),
	scaleMatrix(1),
	currentPosition({0,0,0}),
	currentRotation({0,0,0})
{
	xScale = yScale = zScale = 0;
}

void SceneComponent::Init() {
	BaseComponent::Init();
}

void SceneComponent::Tick(double deltaTime) {
	BaseComponent::Tick(deltaTime);
}

void SceneComponent::Translate(glm::vec3 translation) {
	currentPosition += translation;
	applyTranslation(translation);
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

void SceneComponent::SetPosition(glm::vec3 translation) {
	applyTranslation(translation - currentPosition);
	currentPosition = translation;
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

glm::vec3 SceneComponent::GetPosition() const {
	return currentPosition;
}


void SceneComponent::applyTranslation(glm::vec3 translation) {
	glm::mat4 transMat{
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{translation.x, translation.y, translation.z, 1}
	};

	translationMatrix = translationMatrix * transMat;
}

void SceneComponent::applyScale(double x, double y, double z) {

}
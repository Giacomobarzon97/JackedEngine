#include "SceneComponent.h"

SceneComponent::SceneComponent(ComponentInitializer initializer) :
	BaseComponent(initializer),
	modelMatrix(1),
	currentPosition({0,0,0}),
	currentRotation({0,0,0})
{
}

void SceneComponent::Init() {
	BaseComponent::Init();
}

void SceneComponent::Tick(double deltaTime) {
	BaseComponent::Tick(deltaTime);
}

void SceneComponent::Translate(glm::vec3 translation) {
	currentPosition += translation;
	modelMatrix *= Translator(translation).GetTranslationMatrix();
}

void SceneComponent::Rotate(glm::vec3 rotation) {
	modelMatrix *= Rotator(rotation).GetRotationMatrix();
	currentRotation += rotation;
}

void SceneComponent::Scale(const double x, const double y, const double z) {

}

void SceneComponent::SetPosition(glm::vec3 translation) {
	glm::vec3 newTranslation = translation - currentPosition;
	modelMatrix *= Translator(newTranslation).GetTranslationMatrix();
	currentPosition = translation;
}

void SceneComponent::SetRotation(glm::vec3 rotation) {
	glm::vec3 newRotation = rotation - currentRotation;
	modelMatrix *= Rotator(newRotation).GetRotationMatrix();
	currentRotation = rotation;
}

void SceneComponent::SetScale(const double x, const double y, const double z) {

}

glm::vec3 SceneComponent::GetRotation() const {
	return currentRotation;
}

glm::vec3 SceneComponent::GetPosition() const {
	return currentPosition;
}

glm::mat4 SceneComponent::GetModelMatrix() const {
	return modelMatrix;
}

glm::vec3 SceneComponent::GetUpVector() const {
	return upVector;
}
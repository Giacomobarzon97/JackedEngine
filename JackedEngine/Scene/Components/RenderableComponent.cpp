#include "RenderableComponent.h"

RenderableComponent::RenderableComponent(std::string name) :
	SceneComponent(name),
	modelMatrix(1)
{}

void RenderableComponent::Init() {
	SceneComponent::Init();
}

void RenderableComponent::Tick() {
	SceneComponent::Tick();
	
	modelMatrix = glm::mat4(1);

	applyTranslation();
	applyRotation();
	applyScale();
}

void RenderableComponent::applyTranslation() {
	double radAngle;
	glm::mat4 rotMat;

	radAngle = xRot * M_PI / 180;
	rotMat = {
		{1,0,0,0},
		{0, cos(radAngle), -sin(radAngle),0},
		{0, sin(radAngle), cos(radAngle),0},
		{0,0,0,1},
	};
	modelMatrix = modelMatrix * rotMat;

	radAngle = yRot * M_PI / 180;
	rotMat = {
		{cos(radAngle),0,sin(radAngle),0},
		{0, 1, 0,0},
		{-sin(radAngle), 0, cos(radAngle),0},
		{0,0,0,1}
	};
	modelMatrix = modelMatrix * rotMat;

	radAngle = zRot * M_PI / 180;
	rotMat = {
		{cos(radAngle), -sin(radAngle), 0,0},
		{sin(radAngle), cos(radAngle), 0,0},
		{0, 0, 1,0},
		{0,0,0,1}
	};
	modelMatrix = modelMatrix * rotMat;
}

void RenderableComponent::applyRotation() {

}

void RenderableComponent::applyScale() {

}
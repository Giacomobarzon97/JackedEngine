#include "RenderableComponent.h"

RenderableComponent::RenderableComponent(std::string name) :
	SceneComponent(name),
	modelMatrix(1)
{}

void RenderableComponent::Init() {
	SceneComponent::Init();
}

void RenderableComponent::Tick(double deltaTime) {
	SceneComponent::Tick(deltaTime);
	
	modelMatrix = glm::mat4(1);

	applyTranslation();
	applyRotation();
	applyScale();
}

void RenderableComponent::applyTranslation() {
	glm::mat4 transMat{
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{xTrans, yTrans, zTrans, 1}
	};

	modelMatrix = modelMatrix * transMat;
}

void RenderableComponent::applyRotation() {
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

void RenderableComponent::applyScale() {

}
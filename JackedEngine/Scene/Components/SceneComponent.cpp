#include "SceneComponent.h"

SceneComponent::SceneComponent(std::string name) :
	BaseComponent(name)
{
	xTrans = yTrans = zTrans = 0;
	xRot = yRot = zRot = 0;
	xScale = yScale = zScale = 0;
}

void SceneComponent::Init() {
	BaseComponent::Init();
}

void SceneComponent::Tick() {
	BaseComponent::Tick();
}

void SceneComponent::Translate(const double x, const double y, const double z) {
	xTrans += x;
	yTrans += y;
	zTrans += z;
}

void SceneComponent::Rotate(const double x, const double y, const double z) {
	xRot += x;
	yRot += y;
	zRot += z;
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
	xRot = x;
	yRot = y;
	zRot = z;
}

void SceneComponent::SetScale(const double x, const double y, const double z) {
	xScale = x;
	yScale = y;
	zScale = z;
}
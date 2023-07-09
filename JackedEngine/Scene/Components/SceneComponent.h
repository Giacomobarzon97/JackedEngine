#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include "Scene/Components/BaseComponent.h"

class SceneComponent : public BaseComponent {
public:
	SceneComponent(std::string name);

	virtual void Init();
	virtual void Tick(double deltaTime);

	void Translate(const double x, const double y, const double z);
	void Rotate(const double x, const double y, const double z);
	void Scale(const double x, const double y, const double z);
	void SetPosition(const double x, const double y, const double z);
	void SetRotation(const double x, const double y, const double z);
	void SetScale(const double x, const double y, const double z);

protected:
	glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);

	double xTrans, yTrans, zTrans;
	double xRot, yRot, zRot;
	double xScale, yScale, zScale;

};
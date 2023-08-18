#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include "Scene/Components/BaseComponent.h"

class SceneComponent : public BaseComponent {
public:
	SceneComponent(ComponentInitializer initializer);

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

	glm::mat4 translationMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;

	double xTrans, yTrans, zTrans;
	double pitch, yaw, roll;
	double xScale, yScale, zScale;

private:
	void applyTranslation(double x, double y, double z);
	void applyRotation(double x, double y, double z);
	void applyScale(double x, double y, double z);
};
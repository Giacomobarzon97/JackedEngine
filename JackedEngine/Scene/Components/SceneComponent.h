#pragma once
#include <string>
#include "Scene/Components/BaseComponent.h"
#include "Utils/Rotator.h"

class SceneComponent : public BaseComponent {
public:
	SceneComponent(ComponentInitializer initializer);

	virtual void Init();
	virtual void Tick(double deltaTime);

	void Translate(const double x, const double y, const double z);
	void Rotate(glm::vec3 rotation);
	void Scale(const double x, const double y, const double z);
	void SetPosition(const double x, const double y, const double z);
	void SetRotation(glm::vec3 rotation);
	void SetScale(const double x, const double y, const double z);
	glm::vec3 GetRotation() const;
	glm::vec3 GetTranslation() const;

protected:
	glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 translationMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;

private:
	double xTrans, yTrans, zTrans;
	glm::vec3 currentRotation;
	double xScale, yScale, zScale;

	void applyTranslation(double x, double y, double z);
	void applyScale(double x, double y, double z);
};
#pragma once
#include <string>
#include "Scene/Components/BaseComponent.h"
#include "Utils/Rotator.h"
#include "Utils/Translator.h"

class SceneComponent : public BaseComponent {
public:
	SceneComponent(ComponentInitializer initializer);

	virtual void Init();
	virtual void Tick(double deltaTime);

	void Translate(glm::vec3 translation);
	void Rotate(glm::vec3 rotation);
	void Scale(const double x, const double y, const double z);
	void SetPosition(glm::vec3 translation);
	void SetRotation(glm::vec3 rotation);
	void SetScale(const double x, const double y, const double z);
	glm::vec3 GetRotation() const;
	glm::vec3 GetPosition() const;
	glm::mat4 GetModelMatrix() const;
	glm::vec3 GetUpVector() const;

private:
	glm::vec3 currentPosition;
	glm::vec3 currentRotation;
	glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 modelMatrix;
};
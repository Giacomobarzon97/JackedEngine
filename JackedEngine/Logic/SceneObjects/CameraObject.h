#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Logic/SceneObjects/BaseSceneObject.h"
#include "Windows/BaseWindow.h"

class CameraObject : public BaseSceneObject
{
public:
	CameraObject(BaseWindow& window);

	virtual void Rotate(float x, float y, float z) override;
	virtual void Translate(float x, float y, float z) override;
	virtual void SetPosition(float x, float y, float z) override;
	virtual void SetRotation(float x, float y, float z) override;

	glm::mat4 GetViewProjectionMatrix() const;

private:
	BaseWindow& window;

	glm::vec3 upVector = glm::vec3(0.0f,0.0f,1.0f);
	float drawDistance = 2;

	glm::vec3 eye;
	glm::vec3 center;
};
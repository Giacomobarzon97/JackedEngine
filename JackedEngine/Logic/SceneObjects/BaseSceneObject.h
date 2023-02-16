#pragma once
#include <glm/glm.hpp>

class BaseSceneObject {
public:
	virtual void Rotate(float x, float y, float z) = 0;
	virtual void Translate(float x, float y, float z) = 0;
	virtual void SetPosition(float x, float y, float z) = 0;
	virtual void SetRotation(float x, float y, float z) = 0;

protected:
	static const glm::vec3 UP_VECTOR;
};
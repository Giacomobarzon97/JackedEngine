#pragma once
#include <glm/glm.hpp>

class BaseSceneObject {
public:
	virtual ~BaseSceneObject();
	virtual void Rotate(const double x, const double y, const double z) = 0;
	virtual void Translate(const double x, const double y, const double z) = 0;
	virtual void SetPosition(const double x, const double y, const double z) = 0;
	virtual void SetRotation(const double x, const double y, const double z) = 0;

protected:
	static const glm::vec3 UP_VECTOR;
};
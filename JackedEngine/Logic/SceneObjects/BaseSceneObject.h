#pragma once
#include <string>
#include <glm/glm.hpp>

class BaseSceneObject {
public:
	BaseSceneObject(const std::string name);
	virtual ~BaseSceneObject();

	const std::string GetName() const;

	virtual void Rotate(const double x, const double y, const double z) = 0;
	virtual void Translate(const double x, const double y, const double z) = 0;
	virtual void SetPosition(const double x, const double y, const double z) = 0;
	virtual void SetRotation(const double x, const double y, const double z) = 0;

private:
	std::string name;
};
#pragma once
#include <glm/glm.hpp>

class Rotator {
public:
	Rotator();
	Rotator(glm::vec3);

	glm::vec3 GetRotation() const;
	void SetRotation(glm::vec3 axis);
	glm::mat4 GetRotationMatrix();

private:
	glm::vec3 axis;
};
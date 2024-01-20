#pragma once
#include <glm/glm.hpp>

class Scaler {
public:
	Scaler();
	Scaler(glm::vec3);

	glm::vec3 GetScale() const;
	void SetScale(glm::vec3 axis);
	glm::mat4 GetScaleMatrix();

private:
	glm::vec3 scale;
};
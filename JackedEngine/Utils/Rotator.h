#pragma once
#include <glm/glm.hpp>

class Rotator {
public:
	Rotator();
	Rotator(glm::vec3);

	glm::vec3 GetRotation() const;
	void SetRotation(glm::vec3 axis);
	void SetPitch(float value);
	void SetYaw(float value);
	void SetRoll(float value);
	float GetPitch();
	float GetYaw();
	float GetRoll();
	glm::mat4 GetRotationMatrix();

private:
	glm::vec3 rotation;
};
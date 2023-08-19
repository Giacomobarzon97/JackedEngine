#pragma once
#include <glm/glm.hpp>

class Translator {
public:
	Translator();
	Translator(glm::vec3);

	glm::vec3 GetTranslation() const;
	void SetTranslation(glm::vec3 axis);
	glm::mat4 GetTranslationMatrix();

private:
	glm::vec3 axis;
};
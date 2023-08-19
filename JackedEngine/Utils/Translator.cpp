#include "Translator.h"

Translator::Translator() :
	axis({0,0,0})
{}

Translator::Translator(glm::vec3 axis) :
	axis({glm::radians(axis.x), glm::radians(axis.y), glm::radians(axis.z)})
{}

glm::vec3 Translator::GetTranslation() const {
	return axis;
}

void Translator::SetTranslation(glm::vec3 axis) {
	this->axis = {glm::radians(axis.x), glm::radians(axis.y), glm::radians(axis.z)};
}

glm::mat4 Translator::GetTranslationMatrix() {
	glm::mat4 transMat{
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{axis.x, axis.y, axis.z, 1}
	};

	return transMat;
}
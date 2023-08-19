#include "Translator.h"

Translator::Translator() :
	translation({0,0,0})
{}

Translator::Translator(glm::vec3 translation) :
	translation({glm::radians(translation.x), glm::radians(translation.y), glm::radians(translation.z)})
{}

glm::vec3 Translator::GetTranslation() const {
	return translation;
}

void Translator::SetTranslation(glm::vec3 translation) {
	this->translation = {glm::radians(translation.x), glm::radians(translation.y), glm::radians(translation.z)};
}

glm::mat4 Translator::GetTranslationMatrix() {
	glm::mat4 transMat{
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{translation.x, translation.y, translation.z, 1}
	};

	return transMat;
}
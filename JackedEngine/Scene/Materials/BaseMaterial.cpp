#include "BaseMaterial.h"

BaseMaterial::BaseMaterial(std::string name) : 
	name(name)
{
	materialReference = JackedEngine::GetRenderer().CreateMaterialUniformReference(name);
}

BaseMaterial::~BaseMaterial() {}

std::string BaseMaterial::GetName() const {
	return name;
}

const RendererMaterialUniformReference BaseMaterial::GetMaterialReference() const {
	return materialReference;
}

void BaseMaterial::SetAmbientReflectionCoefficients(glm::vec3 coeffients) {
	materialReference.SetAmbientCoefficients(coeffients);
}

void BaseMaterial::SetDiffuseReflectionCoefficients(glm::vec3 coeffients) {
	materialReference.SetDiffuseCoefficients(coeffients);
}

void BaseMaterial::SetSpecularReflectionCoefficients(glm::vec3 coeffients) {
	materialReference.SetSpecularCoefficients(coeffients);
}
#include "BaseMaterial.h"

BaseMaterial::BaseMaterial(std::string name) : 
	name(name)
{
	materialReference = JackedEngine::GetRenderer().CreateMaterialUniformReference(name);
	materialReference.SetAmbientCoefficients({0.1, 0.1, 0.1});
	materialReference.SetDiffuseCoefficients({ 0.5, 0.5, 0.5 });
	materialReference.SetSpecularCoefficients({ 1, 1, 1 });
	materialReference.SetShininess(32);
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
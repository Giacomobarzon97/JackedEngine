#include "SkyboxComponent.h"

void SkyboxComponent::Init() {
	CPUCubeModel mesh;
	modelRef = JackedEngine::GetRenderer().CreateModel(mesh);
}

void SkyboxComponent::Draw() const {
	if (material.has_value()) {
		glm::mat4 identity(1);
		JackedEngine::GetRenderer().Draw(SKYBOX, modelRef, material.value()->GetDiffuseTexture(), &identity);
	}
}

void SkyboxComponent::SetMaterial(const CubemapMaterial& material) {
	this->material = &material;
}

void SkyboxComponent::Rotate(const double x, const double y, const double z) {

}

void SkyboxComponent::Translate(const double x, const double y, const double z) {

}

void SkyboxComponent::Scale(const double x, const double y, const double z) {

}

void SkyboxComponent::SetPosition(const double x, const double y, const double z) {

}

void SkyboxComponent::SetRotation(const double x, const double y, const double z) {

}

void SkyboxComponent::SetScale(const double x, const double y, const double z) {

}

const glm::mat4 SkyboxComponent::GetModelMatrix() const {
	return modelMatrix;
}
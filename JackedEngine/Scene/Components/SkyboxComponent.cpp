#include "SkyboxComponent.h"

void SkyboxComponent::Init() {
	CPUCubeModel mesh;
	modelRef = JackedEngine::GetRenderer().CreateModel(mesh);
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

void SkyboxComponent::Draw() const {
	if (material.has_value()) {
		JackedEngine::GetRenderer().Draw(modelRef, material.value()->GetDiffuseTexture(), modelMatrix, SKYBOX);
	}
}
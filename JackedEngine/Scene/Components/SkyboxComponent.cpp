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

const ModelReference SkyboxComponent::GetModel() const {
	return modelRef;
}

const ShaderType SkyboxComponent::GetShaderType() const {
	return SKYBOX;
}

const CubemapMaterial& SkyboxComponent::GetMaterial() const {
	return *material.value();
}

const glm::mat4 SkyboxComponent::GetModelMatrix() const {
	return modelMatrix;
}
#include "SkyboxComponent.h"

SkyboxComponent::SkyboxComponent(std::string name) :
	RenderableComponent(name)
{
	uniformReference = JackedEngine::GetRenderer().CreateComponentUniform(name);
	componentData.modelMatrix = glm::mat4(1);
}

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

void SkyboxComponent::Tick() {
	if (material.has_value()) {
		JackedEngine::GetRenderer().UpdateComponentData(uniformReference, componentData);
		JackedEngine::GetRenderer().Draw(modelRef, material.value()->GetDiffuseTexture(), uniformReference, SKYBOX);
	}
}
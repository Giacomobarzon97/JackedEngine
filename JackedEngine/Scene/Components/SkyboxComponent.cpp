#include "SkyboxComponent.h"

SkyboxComponent::SkyboxComponent(const std::string name, const CubemapMaterial& material) :
	RenderableComponent(name),
	modelPath(modelPath),
	material(material)
{
	CPUCubeModel mesh;
	modelRef = JackedEngine::Renderer().CreateModel(mesh);
}

void SkyboxComponent::Draw() {
	glm::mat4 identity(1);
	JackedEngine::Renderer().Draw(SKYBOX, modelRef, material.GetDiffuseTexture(), &identity);
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
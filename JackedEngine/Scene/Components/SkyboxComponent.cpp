#include "SkyboxComponent.h"

SkyboxComponent::SkyboxComponent(const std::string name, const std::string front, const std::string back, const std::string top, const std::string bottom, const std::string right, const std::string left) :
	RenderableComponent(name),
	modelPath(modelPath),
	texturePath(texturePath)
{
	CPUImage texture({front, back, top, bottom, right, left}, CUBEMAP);
	CPUCubeModel mesh;
	textureRef = JackedEngine::Renderer().CreateTexture(texture);
	modelRef = JackedEngine::Renderer().CreateModel(mesh);
}

void SkyboxComponent::Draw() {
	glm::mat4 identity(1);
	JackedEngine::Renderer().Draw(SKYBOX, modelRef, textureRef, &identity);
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
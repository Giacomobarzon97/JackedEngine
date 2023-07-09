#include "SkyboxComponent.h"

SkyboxComponent::SkyboxComponent(std::string name) :
	RenderableComponent(name)
{
	uniformReference = JackedEngine::GetRenderer().CreateMeshUniform(name);
	componentData.modelMatrix = glm::mat4(1);
}

void SkyboxComponent::Init() {
	RenderableComponent::Init();

	CPUCubeModel mesh;
	modelRef = JackedEngine::GetRenderer().CreateModel(mesh);
}

void SkyboxComponent::SetMaterial(const CubemapMaterial& material) {
	this->material = &material;
}

void SkyboxComponent::Tick(double deltaTime) {
	RenderableComponent::Tick(deltaTime);

	componentData.modelMatrix = modelMatrix;

	if (material.has_value()) {
		JackedEngine::GetRenderer().UpdateMeshUniformData(uniformReference, componentData);
		JackedEngine::GetRenderer().Draw(modelRef, material.value()->GetDiffuseTexture(), uniformReference, SKYBOX);
	}
}
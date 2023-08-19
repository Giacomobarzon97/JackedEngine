#include "SkyboxComponent.h"

SkyboxComponent::SkyboxComponent(ComponentInitializer initializer) :
	RenderableComponent(initializer)
{
	uniformReference = JackedEngine::GetRenderer().CreateMeshUniform(GetActorOwner().GetName() + GetName());
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

	if (material.has_value()) {
		componentData.modelMatrix = GetModelMatrix();
		JackedEngine::GetRenderer().UpdateMeshUniformData(uniformReference, componentData);
		JackedEngine::GetRenderer().Draw(modelRef, material.value()->GetDiffuseTexture(), uniformReference, SKYBOX);
	}
}
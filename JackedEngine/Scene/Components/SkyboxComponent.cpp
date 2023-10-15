#include "SkyboxComponent.h"

SkyboxComponent::SkyboxComponent(ComponentInitializer initializer) :
	RenderableComponent(initializer)
{}

void SkyboxComponent::Init() {
	RenderableComponent::Init();

	uniformReference = JackedEngine::GetRenderer().CreateMeshUniform(GetActorOwner().GetName() + GetName());
	CPUCubeModel mesh;
	modelRef = JackedEngine::GetRenderer().CreateModel(mesh);
}

void SkyboxComponent::SetMaterial(const CubemapMaterial& material) {
	this->material = &material;
}

void SkyboxComponent::Tick(double deltaTime) {
	RenderableComponent::Tick(deltaTime);

	if (material.has_value()) {
		uniformReference.SetModelMatrix(GetModelMatrix());
		uniformReference.Update();
		JackedEngine::GetRenderer().DrawSkybox(modelRef, material.value()->GetDiffuseTexture(), uniformReference);
	}
}
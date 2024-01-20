#include "QuadMeshComponent.h"

QuadMeshComponent::QuadMeshComponent(ComponentInitializer initializer) :
	RenderableComponent(initializer)
{
	BaseActor& actorOwner = GetActorOwner();
}

void QuadMeshComponent::Init() {
	RenderableComponent::Init();

	uniformReference = JackedEngine::GetRenderer().CreateMeshUniform(GetActorOwner().GetName() + GetName());
	CPUQuadModel mesh{};
	modelRef = JackedEngine::GetRenderer().CreateModel(mesh);
}

void QuadMeshComponent::SetMaterial(const GenericMeshMaterial& material) {
	this->material = &material;
}

void QuadMeshComponent::Tick(double deltaTime) {
	RenderableComponent::Tick(deltaTime);

	if (material.has_value() && modelRef.has_value()) {
		uniformReference.SetModelMatrix(GetModelMatrix());
		uniformReference.Update();
		JackedEngine::GetRenderer().DrawTextured3DMesh(
			modelRef.value(),
			material.value()->GetDiffuseTexture(),
			uniformReference,
			material.value()->GetMaterialReference()
		);
	}
}
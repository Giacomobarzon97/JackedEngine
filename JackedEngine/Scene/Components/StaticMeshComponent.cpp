#include "StaticMeshComponent.h"

StaticMeshComponent::StaticMeshComponent(ComponentInitializer initializer) :
	RenderableComponent(initializer),
	uniformReference(JackedEngine::GetRenderer().CreateMeshUniform(GetActorOwner().GetName() + GetName()))
{
	BaseActor& actorOwner = GetActorOwner();
}

void StaticMeshComponent::Init() {
	RenderableComponent::Init();
}

void StaticMeshComponent::SetModelPath(const std::string modelPath) {
	CPUGenericMesh mesh(modelPath, true, true);
	modelRef = JackedEngine::GetRenderer().CreateModel(mesh);
}

void StaticMeshComponent::SetMaterial(const GenericMeshMaterial& material) {
	this->material = &material;
}

void StaticMeshComponent::Tick(double deltaTime) {
	RenderableComponent::Tick(deltaTime);

	if (material.has_value() && modelRef.has_value()) {
		uniformReference.SetModelMatrix(GetModelMatrix());
		uniformReference.Update();
		JackedEngine::GetRenderer().DrawTextured3DMesh(modelRef.value(), material.value()->GetDiffuseTexture(), uniformReference);
	}
}
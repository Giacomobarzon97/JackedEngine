#include "StaticMeshComponent.h"

StaticMeshComponent::StaticMeshComponent(ComponentInitializer initializer) :
	RenderableComponent(initializer)
{
	BaseActor& actorOwner = GetActorOwner();
}

void StaticMeshComponent::Init() {
	RenderableComponent::Init();

	uniformReference = JackedEngine::GetRenderer().CreateMeshUniform(GetActorOwner().GetName() + GetName());
	CPUGenericMesh mesh(modelPath);
	modelRef = JackedEngine::GetRenderer().CreateModel(mesh);
}

void StaticMeshComponent::SetModelPath(const std::string modelPath) {
	this->modelPath = modelPath;
}

void StaticMeshComponent::SetMaterial(const GenericMeshMaterial& material) {
	this->material = &material;
}

void StaticMeshComponent::Tick(double deltaTime) {
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
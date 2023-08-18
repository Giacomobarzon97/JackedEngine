#include "StaticMeshComponent.h"

StaticMeshComponent::StaticMeshComponent(ComponentInitializer initializer) :
	RenderableComponent(initializer)
{
	BaseActor& actorOwner = GetActorOwner();
	uniformReference = JackedEngine::GetRenderer().CreateMeshUniform(GetActorOwner().GetName() + GetName());
	componentData.translationMatrix = translationMatrix;
	componentData.rotationMatrix = rotationMatrix;
	componentData.scaleMatrix = scaleMatrix;
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
		componentData.translationMatrix = translationMatrix;
		componentData.rotationMatrix = rotationMatrix;
		componentData.scaleMatrix = scaleMatrix;

		JackedEngine::GetRenderer().UpdateMeshUniformData(uniformReference, componentData);
		JackedEngine::GetRenderer().Draw(modelRef.value(), material.value()->GetDiffuseTexture(), uniformReference, OBJECT3D);
	}
}
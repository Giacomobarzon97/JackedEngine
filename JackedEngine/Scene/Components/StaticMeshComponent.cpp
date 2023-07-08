#include "StaticMeshComponent.h"

StaticMeshComponent::StaticMeshComponent(std::string name) :
	RenderableComponent(name)
{
	uniformReference = JackedEngine::GetRenderer().CreateMeshUniform(name);
	componentData.modelMatrix = glm::mat4(1);
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

void StaticMeshComponent::Tick() {
	RenderableComponent::Tick();

	if (material.has_value() && modelRef.has_value()) {
		componentData.modelMatrix = modelMatrix;

		JackedEngine::GetRenderer().UpdateMeshUniformData(uniformReference, componentData);
		JackedEngine::GetRenderer().Draw(modelRef.value(), material.value()->GetDiffuseTexture(), uniformReference, OBJECT3D);
	}
}
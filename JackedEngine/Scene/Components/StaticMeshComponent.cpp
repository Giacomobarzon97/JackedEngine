#include "StaticMeshComponent.h"

StaticMeshComponent::StaticMeshComponent(std::string name) :
	RenderableComponent(name)
{
	uniformReference = JackedEngine::GetRenderer().CreateMeshUniform(name);
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
	//Rotate(0, 10 * deltaTime, 0);

	if (material.has_value() && modelRef.has_value()) {
		componentData.translationMatrix = translationMatrix;
		componentData.rotationMatrix = rotationMatrix;
		componentData.scaleMatrix = scaleMatrix;

		JackedEngine::GetRenderer().UpdateMeshUniformData(uniformReference, componentData);
		JackedEngine::GetRenderer().Draw(modelRef.value(), material.value()->GetDiffuseTexture(), uniformReference, OBJECT3D);
	}
}
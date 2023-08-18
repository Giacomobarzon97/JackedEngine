#pragma once
#include <string>
#include <optional>
#include "Scene/Components/RenderableComponent.h"
#include "Scene/Materials/GenericMeshMaterial.h"
#include "Backends/CPUResources/CPUModels/CPUGenericMesh.h"
#include "Scene/Actors/BaseActor.h"

class StaticMeshComponent : public RenderableComponent {
public:
	StaticMeshComponent(ComponentInitializer initializer);

	virtual void Init() override;
	void Tick(double deltaTime) override;

	void SetModelPath(const std::string modelPath);
	void SetMaterial(const GenericMeshMaterial& material);

private:
	MeshUniformData componentData;
	UniformReference uniformReference;
	std::optional<const GenericMeshMaterial*> material;
	std::optional<ModelReference> modelRef;
};
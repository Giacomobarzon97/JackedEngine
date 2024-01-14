#pragma once
#include <string>
#include <optional>
#include "Scene/Components/RenderableComponent.h"
#include "Scene/Materials/GenericMeshMaterial.h"
#include "Backends/CPUResources/CPUModels/CPUQuadModel.h"
#include "Scene/Actors/BaseActor.h"

class QuadMeshComponent : public RenderableComponent {
public:
	QuadMeshComponent(ComponentInitializer initializer);

	virtual void Init() override;
	virtual void Tick(double deltaTime) override;

	void SetMaterial(const GenericMeshMaterial& material);

private:
	RendererMeshUniformReference uniformReference;
	std::optional<const GenericMeshMaterial*> material;
	std::optional<RendererModelReference> modelRef;
};
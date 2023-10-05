#pragma once
#include <optional>
#include <string>
#include "Scene/Components/RenderableComponent.h"
#include "Scene/Materials/CubemapMaterial.h"
#include "Backends/CPUResources/CPUModels/CPUCubeModel.h"
#include "Scene/Actors/BaseActor.h"

class SkyboxComponent : public RenderableComponent {
public:
	SkyboxComponent(ComponentInitializer initializer);

	virtual void Init() override;
	virtual void Tick(double deltaTime) override;

	void SetMaterial(const CubemapMaterial& material);

private:
	MeshUniformData componentData;
	BackendUniformReference uniformReference;
	BackendModelReference modelRef;
	std::optional<const CubemapMaterial*> material;
};
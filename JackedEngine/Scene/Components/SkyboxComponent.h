#pragma once
#include <optional>
#include <string>
#include "Scene/Components/RenderableComponent.h"
#include "Scene/Materials/CubemapMaterial.h"
#include "Backends/CPUResources/CPUModels/CPUCubeModel.h"

class SkyboxComponent : public RenderableComponent {
public:
	SkyboxComponent(std::string name);

	virtual void Init() override;
	virtual void Tick() override;

	void SetMaterial(const CubemapMaterial& material);

private:
	MeshUniformData componentData;
	UniformReference uniformReference;
	ModelReference modelRef;
	std::optional<const CubemapMaterial*> material;
};
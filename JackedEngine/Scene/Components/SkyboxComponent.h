#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
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

	virtual void Rotate(const double x, const double y, const double z) override;
	virtual void Translate(const double x, const double y, const double z) override;
	void Scale(const double x, const double y, const double z) override;
	virtual void SetPosition(const double x, const double y, const double z) override;
	virtual void SetRotation(const double x, const double y, const double z) override;
	void SetScale(const double x, const double y, const double z) override;

private:
	ComponentData componentData;
	UniformReference uniformReference;
	ModelReference modelRef;
	std::optional<const CubemapMaterial*> material;
};
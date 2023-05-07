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
	virtual void Init() override;

	void SetMaterial(const CubemapMaterial& material);

	virtual void Rotate(const double x, const double y, const double z) override;
	virtual void Translate(const double x, const double y, const double z) override;
	void Scale(const double x, const double y, const double z) override;
	virtual void SetPosition(const double x, const double y, const double z) override;
	virtual void SetRotation(const double x, const double y, const double z) override;
	void SetScale(const double x, const double y, const double z) override;

	virtual const ShaderType GetShaderType() const override;
	virtual const ModelReference GetModel() const override;
	virtual const CubemapMaterial& GetMaterial() const override;
	virtual const glm::mat4 GetModelMatrix() const override;

private:
	glm::mat4 modelMatrix = glm::mat4(1);
	ModelReference modelRef;
	std::optional<const CubemapMaterial*> material;
};
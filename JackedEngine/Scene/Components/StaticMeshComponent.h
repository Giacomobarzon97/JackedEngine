#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <optional>
#include "Scene/Components/RenderableComponent.h"
#include "Scene/Materials/GenericMeshMaterial.h"
#include "Backends/CPUResources/CPUModels/CPUGenericMesh.h"

class StaticMeshComponent : public RenderableComponent {
public:
	virtual void Init() override;

	void SetModelPath(const std::string modelPath);
	void SetMaterial(const GenericMeshMaterial& material);

	virtual void Rotate(const double x, const double y, const double z) override;
	virtual void Translate(const double x, const double y, const double z) override;
	void Scale(const double x, const double y, const double z) override;
	virtual void SetPosition(const double x, const double y, const double z) override;
	virtual void SetRotation(const double x, const double y, const double z) override;
	void SetScale(const double x, const double y, const double z) override;

	virtual const ShaderType GetShaderType() const override;
	virtual const ModelReference GetModel() const override;
	virtual const GenericMeshMaterial& GetMaterial() const override;
	virtual const glm::mat4 GetModelMatrix() const override;

private:
	glm::mat4 modelMatrix = glm::mat4(1);
	std::optional<const GenericMeshMaterial*> material;
	std::optional<ModelReference> modelRef;
};
#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include "Scene/Components/RenderableComponent.h"
#include "Scene/Materials/GenericMeshMaterial.h"
#include "Backends/CPUResources/CPUModels/CPUGenericMesh.h"

class StaticMeshComponent : public RenderableComponent {
public:
	StaticMeshComponent(const std::string name, const std::string modelPath, const GenericMeshMaterial& material);

	virtual void Rotate(const double x, const double y, const double z) override;
	virtual void Translate(const double x, const double y, const double z) override;
	void Scale(const double x, const double y, const double z) override;
	virtual void SetPosition(const double x, const double y, const double z) override;
	virtual void SetRotation(const double x, const double y, const double z) override;
	void SetScale(const double x, const double y, const double z) override;

	virtual void Draw() override;

	const glm::mat4 GetModelMatrix() const;

private:
	glm::mat4 modelMatrix = glm::mat4(1);
	const GenericMeshMaterial& material;
	ModelReference modelRef;
};
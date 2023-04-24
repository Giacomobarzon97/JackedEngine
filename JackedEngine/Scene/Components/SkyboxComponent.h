#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include "JackedEngine.h"
#include "Scene/Components/RenderableComponent.h"
#include "Backends/CPUResources/CPUModels/CPUCubeModel.h"

class SkyboxComponent : public RenderableComponent {
public:
	SkyboxComponent(const std::string name, const std::string front, const std::string back, const std::string top, const std::string bottom, const std::string right, const std::string left);

	virtual void Rotate(const double x, const double y, const double z) override;
	virtual void Translate(const double x, const double y, const double z) override;
	void Scale(const double x, const double y, const double z) override;
	virtual void SetPosition(const double x, const double y, const double z) override;
	virtual void SetRotation(const double x, const double y, const double z) override;
	void SetScale(const double x, const double y, const double z) override;

	virtual void Draw() override;

	const glm::mat4 GetModelMatrix() const;

private:
	std::string modelPath;
	std::string texturePath;
	glm::mat4 modelMatrix = glm::mat4(1);

	TextureReference textureRef;
	ModelReference modelRef;
};
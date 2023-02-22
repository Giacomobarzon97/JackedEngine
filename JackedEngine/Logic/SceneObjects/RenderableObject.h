#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <optional>
#include "Logic/SceneObjects/BaseSceneObject.h"
#include "Logic/Model.h"

class RenderableObject : public BaseSceneObject	{
public:
	RenderableObject(const Model& model);

	virtual void Rotate(const double x, const double y, const double z) override;
	virtual void Translate(const double x, const double y, const double z) override;
	void Scale(const double x, const double y, const double z);
	virtual void SetPosition(const double x, const double y, const double z) override;
	virtual void SetRotation(const double x, const double y, const double z) override;
	void SetScale(const double x, const double y, const double z);

	void SetTexture(const std::string texturePath);
	const std::optional<std::string> GetTexture() const;

	const glm::mat4 GetModelMatrix() const;
	const Model& GetModel() const;

private:
	const Model& model;
	std::optional<std::string> texturePath;
	glm::mat4 modelMatrix = glm::mat4(1);
};
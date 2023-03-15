#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include "Scene/SceneObjects/BaseSceneObject.h"

class RenderableObject : public BaseSceneObject	{
public:
	RenderableObject(const std::string name, const std::string modelPath, const std::string texturePath);

	virtual void Rotate(const double x, const double y, const double z) override;
	virtual void Translate(const double x, const double y, const double z) override;
	void Scale(const double x, const double y, const double z);
	virtual void SetPosition(const double x, const double y, const double z) override;
	virtual void SetRotation(const double x, const double y, const double z) override;
	void SetScale(const double x, const double y, const double z);

	const std::string GetTexturePath() const;
	const std::string GetModelPath() const;

	const glm::mat4 GetModelMatrix() const;

private:
	std::string modelPath;
	std::string texturePath;
	glm::mat4 modelMatrix = glm::mat4(1);
};
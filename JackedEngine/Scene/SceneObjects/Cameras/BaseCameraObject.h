#pragma once
#include "Scene/SceneObjects/BaseSceneObject.h"

class BaseCameraObject : public BaseSceneObject{
public:
	BaseCameraObject(const std::string name);
	virtual ~BaseCameraObject();

	virtual const glm::mat4 GetViewMatrix() const = 0;
	virtual const glm::mat4 GetProjectionMatrix(const uint32_t width, const uint32_t height) const = 0;
};
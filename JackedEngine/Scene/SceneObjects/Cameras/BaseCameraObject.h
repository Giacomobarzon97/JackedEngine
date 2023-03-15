#pragma once
#include "Scene/SceneObjects/BaseSceneObject.h"

class BaseCameraObject : public BaseSceneObject{
public:
	BaseCameraObject(const std::string name);
	virtual ~BaseCameraObject();
	virtual const glm::mat4 GetViewProjectionMatrix() const = 0;
};
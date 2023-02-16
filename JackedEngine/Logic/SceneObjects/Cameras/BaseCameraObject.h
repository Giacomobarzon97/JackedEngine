#pragma once
#include "Logic/SceneObjects/BaseSceneObject.h"

class BaseCameraObject : public BaseSceneObject{
public:
	virtual ~BaseCameraObject();
	virtual glm::mat4 GetViewProjectionMatrix() const = 0;
};
#pragma once
#include "Rendering/Device.h"
#include "Logic/SceneObjects/Cameras/BaseCameraObject.h"
#include "Logic/SceneObjects/RenderableObject.h"

class BaseDescriptorSet {
public:
	BaseDescriptorSet(const Device& device);
	virtual ~BaseDescriptorSet() = 0;

	const VkDescriptorSet& GetDescriptorSet() const;

protected:
	const Device& device;
	VkDescriptorSet descriptorSet;
};
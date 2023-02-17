#pragma once
#include "Rendering/Device.h"
#include "Logic/SceneObjects/Cameras/BaseCameraObject.h"
#include "Logic/SceneObjects/RenderableObject.h"

class BaseDescriptorSet {
public:
	BaseDescriptorSet(const Device& device);
	virtual ~BaseDescriptorSet() = 0;

	const VkDescriptorSet& GetDescriptorSet() const;

	virtual void UpdateDescriptorSet(const BaseCameraObject& camera, const RenderableObject& object) const = 0;

protected:
	const Device& device;
	VkDescriptorSet descriptorSet;
};
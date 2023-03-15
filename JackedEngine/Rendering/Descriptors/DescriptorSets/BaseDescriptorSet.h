#pragma once
#include <glm/glm.hpp>
#include "Rendering/Device.h"

class BaseDescriptorSet {
public:
	BaseDescriptorSet(const Device& device);
	virtual ~BaseDescriptorSet() = 0;

	const VkDescriptorSet& GetDescriptorSet() const;

protected:
	const Device& device;
	VkDescriptorSet descriptorSet;
};
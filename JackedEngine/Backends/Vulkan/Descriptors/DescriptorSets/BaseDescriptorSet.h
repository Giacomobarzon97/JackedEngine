#pragma once
#include <glm/glm.hpp>
#include "Backends/Vulkan/Device.h"

class BaseDescriptorSet {
public:
	BaseDescriptorSet(const Device& device);
	virtual ~BaseDescriptorSet() = 0;

	const VkDescriptorSet& GetDescriptorSet() const;

protected:
	const Device& device;
	VkDescriptorSet descriptorSet;
};
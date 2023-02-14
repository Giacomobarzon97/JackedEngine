#pragma once
#include "Rendering/Device.h"

class BaseDescriptorSet {
public:
	BaseDescriptorSet(const Device& device);
	virtual ~BaseDescriptorSet() = 0;

	const VkDescriptorSet& GetDescriptorSet() const;

	virtual void UpdateDescriptorSet() const = 0;

protected:
	const Device& device;
	VkDescriptorSet descriptorSet;
};
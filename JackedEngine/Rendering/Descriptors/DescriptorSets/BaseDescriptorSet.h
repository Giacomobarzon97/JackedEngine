#pragma once
#include "Rendering/Device.h"

class BaseDescriptorSet {
public:
	BaseDescriptorSet(const Device* const device);
	virtual ~BaseDescriptorSet() = 0;

	const VkDescriptorSet* const GetDescriptorSet() const;

protected:
	const Device* const device;
	VkDescriptorSet descriptorSet;
};
#pragma once
#include "Backends/Vulkan/Device.h"

class BaseSampler {
public:
	BaseSampler(const Device& device);
	virtual ~BaseSampler() = 0;

	const VkSampler& GetSampler() const;

protected:
	const Device& device;
	VkSampler sampler;

};
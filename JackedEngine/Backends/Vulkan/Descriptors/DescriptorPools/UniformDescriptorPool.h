#pragma once
#include <array>
#include "Backends/Vulkan/Descriptors/DescriptorPools/BaseDescriptorPool.h"

class UniformDescriptorPool : public BaseDescriptorPool{
public:
	UniformDescriptorPool(const Device& device, int maxSets);
	UniformDescriptorPool(UniformDescriptorPool&) = delete;
	virtual ~UniformDescriptorPool() override;

	UniformDescriptorPool&operator=(UniformDescriptorPool&) = delete;

};
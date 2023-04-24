#pragma once
#include <array>
#include "Backends/Vulkan/Descriptors/DescriptorPools/BaseDescriptorPool.h"

class FrameDescriptorPool : public BaseDescriptorPool{
public:
	FrameDescriptorPool(const Device& device, int maxSets);
	FrameDescriptorPool(FrameDescriptorPool&) = delete;
	virtual ~FrameDescriptorPool() override;

	FrameDescriptorPool&operator=(FrameDescriptorPool&) = delete;

};
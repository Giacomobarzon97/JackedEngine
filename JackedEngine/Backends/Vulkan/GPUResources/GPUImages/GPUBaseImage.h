#pragma once
#include<vector>
#include <stdexcept>
#include "Backends/CPUResources/CPUImages/CPUImage2D.h"
#include "Backends/Vulkan/Memory/AllocationFactories/BaseAllocationFactory.h"

class GPUBaseImage {
public:
	virtual ~GPUBaseImage();

	virtual const VkImageView& GetImageView() const = 0;
};
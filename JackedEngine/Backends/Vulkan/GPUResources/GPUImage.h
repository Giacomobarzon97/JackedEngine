#pragma once
#include<vector>
#include <stdexcept>
#include "Backends/CPUResources/CPUImage.h"
#include "Backends/Vulkan/Memory/AllocationFactories/BaseAllocationFactory.h"

class GPUImage {
public:
	GPUImage(const BaseAllocationFactory& allocationFactory, const CPUImage& image);
	GPUImage(GPUImage&) = delete;
	~GPUImage();

	GPUImage& operator=(GPUImage&) = delete;

	const VkImageView& GetImageView() const;

private:
	const BaseImageAllocation* imageBufferAllocation;

};
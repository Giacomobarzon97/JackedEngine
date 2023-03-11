#pragma once
#include "Rendering/Resources/CPUResources/CPUImage.h"
#include "Rendering/Memory/AllocationFactories/BaseAllocationFactory.h"

class GPUImage {
public:
	GPUImage(const BaseAllocationFactory& allocationFactory, const CPUImage& image);
	GPUImage(GPUImage&) = delete;
	~GPUImage();

	GPUImage& operator=(GPUImage&) = delete;

	const VkImageView& GetImageView() const;


private:
	const BaseImageBufferAllocation* imageBufferAllocation;

};
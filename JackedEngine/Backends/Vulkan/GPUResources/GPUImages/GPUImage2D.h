#pragma once
#include<vector>
#include <stdexcept>
#include "Backends/Vulkan/GPUResources/GPUImages/GPUBaseImage.h"
#include "Backends/CPUResources/CPUImages/CPUImage2D.h"
#include "Backends/Vulkan/Memory/AllocationFactories/BaseAllocationFactory.h"

class GPUImage2D : public GPUBaseImage {
public:
	GPUImage2D(const BaseAllocationFactory& allocationFactory, const CPUImage2D& image);
	GPUImage2D(GPUImage2D&) = delete;
	~GPUImage2D();

	GPUImage2D& operator=(GPUImage2D&) = delete;

	virtual const VkImageView& GetImageView() const override;

private:
	const BaseImage2DAllocation* imageBufferAllocation;

};
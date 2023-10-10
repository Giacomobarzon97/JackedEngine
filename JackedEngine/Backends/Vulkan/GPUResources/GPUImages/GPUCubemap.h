#pragma once
#include<vector>
#include <stdexcept>
#include "Backends/Vulkan/GPUResources/GPUImages/GPUBaseImage.h"
#include "Backends/CPUResources/CPUImages/CPUCubemap.h"
#include "Backends/Vulkan/Memory/AllocationFactories/BaseAllocationFactory.h"

class GPUCubemap : public GPUBaseImage{
public:
	GPUCubemap(const BaseAllocationFactory& allocationFactory, const CPUCubemap& image);
	GPUCubemap(GPUCubemap&) = delete;
	~GPUCubemap();

	GPUCubemap& operator=(GPUCubemap&) = delete;

	virtual const VkImageView& GetImageView() const override;

private:
	const BaseCubemapAllocation* imageBufferAllocation;

};
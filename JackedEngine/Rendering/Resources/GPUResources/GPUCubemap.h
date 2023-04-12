#pragma once
#include <stdexcept>
#include <vector>
#include "Rendering/Resources/CPUResources/CPUVertices/CPUPositionVertex.h"
#include "Rendering/Resources/CPUResources/CPUImage.h"
#include "Rendering/Memory/AllocationFactories/BaseAllocationFactory.h"
#include "Rendering/Memory/Allocations/ImageAllocations/BaseImageAllocation.h"

class GPUCubemap {
public:
	GPUCubemap(const BaseAllocationFactory& allocationFactory, const CPUImage& frontFaceData, const CPUImage& backFaceData, const CPUImage& upFaceData, const CPUImage& downFaceData, const CPUImage& rightFaceData, const CPUImage& leftFaceData);
	GPUCubemap(GPUCubemap&) = delete;
	~GPUCubemap();

	GPUCubemap& operator=(GPUCubemap&) = delete;

	const VkImageView& GetImageView() const;

private:
	const BaseImageAllocation* cubemapBuffer;
};
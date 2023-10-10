#pragma once
#include "Backends/Vulkan/Memory/Allocators/VMAAllocator.h"
#include "Backends/Vulkan/Memory/Allocations/Image2DAllocations/BaseImage2DAllocation.h"

class VMAImage2DAllocation : public BaseImage2DAllocation {
public:
	VMAImage2DAllocation(const VMAAllocator& allocator, const void* data, const int width, const int height);
	VMAImage2DAllocation(VMAImage2DAllocation&) = delete;
	~VMAImage2DAllocation();
	VMAImage2DAllocation& operator=(VMAImage2DAllocation&) = delete;

private:
	const VMAAllocator& allocator;
	VmaAllocation allocation;
};
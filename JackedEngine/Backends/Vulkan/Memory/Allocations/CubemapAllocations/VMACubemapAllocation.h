#pragma once
#include "Backends/Vulkan/Memory/Allocators/VMAAllocator.h"
#include "Backends/Vulkan/Memory/Allocations/CubemapAllocations/BaseCubemapAllocation.h"

class VMACubemapAllocation : public BaseCubemapAllocation {
public:
	VMACubemapAllocation(const VMAAllocator& allocator, const std::array<const void*, 6> data, const int width, const int height);
	VMACubemapAllocation(VMACubemapAllocation&) = delete;
	~VMACubemapAllocation();
	VMACubemapAllocation& operator=(VMACubemapAllocation&) = delete;

private:
	const VMAAllocator& allocator;
	VmaAllocation allocation;
};
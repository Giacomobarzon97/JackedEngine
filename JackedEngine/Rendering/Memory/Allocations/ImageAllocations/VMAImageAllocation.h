#pragma once
#include "Rendering/Memory/Allocators/VMAAllocator.h"
#include "Rendering/Memory/Allocations/ImageAllocations/BaseImageAllocation.h"

class VMAImageAllocation : public BaseImageAllocation {
public:
	VMAImageAllocation(const VMAAllocator& allocator, const std::vector<const void*> data, const int width, const int height, VkImageViewType imageViewType, VkImageCreateFlags flags);
	VMAImageAllocation(VMAImageAllocation&) = delete;
	~VMAImageAllocation();
	VMAImageAllocation& operator=(VMAImageAllocation&) = delete;

private:
	const VMAAllocator& allocator;
	VmaAllocation allocation;
};
#pragma once
#include "Backends/Vulkan/Memory/Allocators/VMAAllocator.h"
#include "Backends/Vulkan/Memory/Allocations/BufferAllocations/BaseBufferAllocation.h"

class VMABufferAllocation : public BaseBufferAllocation {
public:
	VMABufferAllocation(const VMAAllocator& allocator, const void* data, const uint32_t dataSize, VkBufferUsageFlags usage);
	VMABufferAllocation(VMABufferAllocation&) = delete;
	~VMABufferAllocation();
	VMABufferAllocation& operator=(VMABufferAllocation&) = delete;

private:
	const VMAAllocator& allocator;
	VmaAllocation allocation;
};
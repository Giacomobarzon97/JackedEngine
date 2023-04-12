#pragma once
#include "Rendering/Memory/Allocators/VMAAllocator.h"
#include "Rendering/Memory/Allocations/BufferAllocations/BaseBufferAllocation.h"

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
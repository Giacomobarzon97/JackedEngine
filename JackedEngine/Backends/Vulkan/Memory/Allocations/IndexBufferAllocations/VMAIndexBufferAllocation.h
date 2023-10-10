#pragma once
#include "Backends/Vulkan/Memory/Allocators/VMAAllocator.h"
#include "Backends/Vulkan/Memory/Allocations/IndexBufferAllocations/BaseIndexBufferAllocation.h"

class VMAIndexBufferAllocation : public BaseIndexBufferAllocation {
public:
	VMAIndexBufferAllocation(const VMAAllocator& allocator, const void* data, const uint32_t dataSize);
	VMAIndexBufferAllocation(VMAIndexBufferAllocation&) = delete;
	~VMAIndexBufferAllocation();
	VMAIndexBufferAllocation& operator=(VMAIndexBufferAllocation&) = delete;

private:
	const VMAAllocator& allocator;
	VmaAllocation allocation;
};
#pragma once
#include "Backends/Vulkan/Memory/Allocators/VMAAllocator.h"
#include "Backends/Vulkan/Memory/Allocations/VertexBufferAllocations/BaseVertexBufferAllocation.h"

class VMAVertexBufferAllocation : public BaseVertexBufferAllocation {
public:
	VMAVertexBufferAllocation(const VMAAllocator& allocator, const void* data, const uint32_t dataSize);
	VMAVertexBufferAllocation(VMAVertexBufferAllocation&) = delete;
	~VMAVertexBufferAllocation();
	VMAVertexBufferAllocation& operator=(VMAVertexBufferAllocation&) = delete;

private:
	const VMAAllocator& allocator;
	VmaAllocation allocation;
};
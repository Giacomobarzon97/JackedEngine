#pragma once
#include "Rendering/Memory/Allocators/VMAAllocator.h"
#include "Rendering/Memory/BufferAllocations/VertexBufferAllocations/BaseVertexBufferAllocation.h"

class VMAVertexBufferAllocation : public BaseVertexBufferAllocation {
public:
	VMAVertexBufferAllocation(const VMAAllocator& allocator, const void* data, const size_t dataSize);
	VMAVertexBufferAllocation(VMAVertexBufferAllocation&) = delete;
	~VMAVertexBufferAllocation();
	VMAVertexBufferAllocation& operator=(VMAVertexBufferAllocation&) = delete;

private:
	const VMAAllocator& allocator;
	VmaAllocation allocation;
};
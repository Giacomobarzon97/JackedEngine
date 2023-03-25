#pragma once
#include "Rendering/Memory/Allocators/VMAAllocator.h"
#include "Rendering/Memory/BufferAllocations/IndexBufferAllocations/BaseIndexBufferAllocation.h"

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
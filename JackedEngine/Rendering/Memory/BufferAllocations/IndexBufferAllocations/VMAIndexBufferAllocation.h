#pragma once
#include "Rendering/Memory/Allocators/VMAAllocator.h"
#include "Rendering/Memory/BufferAllocations/IndexBufferAllocations/BaseIndexBufferAllocation.h"

class VMAIndexBufferAllocation : public BaseIndexBufferAllocation {
public:
	VMAIndexBufferAllocation(const VMAAllocator& allocator, const void* data, const size_t dataSize);
	VMAIndexBufferAllocation(VMAIndexBufferAllocation&) = delete;
	~VMAIndexBufferAllocation();
	VMAIndexBufferAllocation& operator=(VMAIndexBufferAllocation&) = delete;

	virtual const VkDeviceSize GetOffset() const override;

private:
	const VMAAllocator& allocator;
	VmaAllocation allocation;
};
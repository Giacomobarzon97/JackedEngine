#pragma once
#include "Rendering/Memory/Allocators/VMAAllocator.h"
#include "Rendering/Memory/BufferAllocations/BaseBufferAllocation.h"

class VMABufferAllocation : public BaseBufferAllocation {
public:
	VMABufferAllocation(const VMAAllocator& allocator, const void* data, const size_t dataSize);
	VMABufferAllocation(VMABufferAllocation&) = delete;
	~VMABufferAllocation();
	VMABufferAllocation& operator=(VMABufferAllocation&) = delete;

	virtual const VkDeviceSize GetOffset() const override;

private:
	const VMAAllocator& allocator;
	VmaAllocation allocation;
};
#pragma once
#include "Rendering/Memory/Allocators/VMAAllocator.h"
#include "Rendering/Memory/Allocations/BaseAllocation.h"

class VMAAllocation : public BaseAllocation{
public:
	VMAAllocation(const VMAAllocator& allocator, const void* data, const size_t dataSize);
	~VMAAllocation();

	virtual const VkDeviceSize GetOffset() const override;

private:
	const VMAAllocator& allocator;
	VmaAllocation allocation;
};
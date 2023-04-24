#pragma once
#include "Backends/Vulkan/Memory/Allocators/VMAAllocator.h"
#include "Backends/Vulkan/Memory/Allocations/UniformAllocations/BaseUniformAllocation.h"

class VMAUniformAllocation : public BaseUniformAllocation {
public:
	VMAUniformAllocation(const VMAAllocator& allocator, const uint32_t dataSize);
	VMAUniformAllocation(VMAUniformAllocation&) = delete;
	~VMAUniformAllocation();
	VMAUniformAllocation& operator=(VMAUniformAllocation&) = delete;

	virtual void UpdateBuffer(const void* data) const override;

private:
	const VMAAllocator& allocator;
	VmaAllocation allocation;
	void* memLoc;
	VkDeviceSize bufferSize;
};
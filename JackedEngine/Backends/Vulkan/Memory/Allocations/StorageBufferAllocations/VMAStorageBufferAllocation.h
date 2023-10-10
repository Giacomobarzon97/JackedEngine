#pragma once
#include "Backends/Vulkan/Memory/Allocators/VMAAllocator.h"
#include "Backends/Vulkan/Memory/Allocations/StorageBufferAllocations/BaseStorageBufferAllocation.h"

class VMAStorageBufferAllocation : public BaseStorageBufferAllocation {
public:
	VMAStorageBufferAllocation(const VMAAllocator& allocator, const uint32_t elementSize, const uint32_t nElements);
	VMAStorageBufferAllocation(VMAStorageBufferAllocation&) = delete;
	~VMAStorageBufferAllocation();
	VMAStorageBufferAllocation& operator=(VMAStorageBufferAllocation&) = delete;

	virtual void UpdateBuffer(const void* data, const uint32_t nElements) const override;

private:
	const VMAAllocator& allocator;
	VmaAllocation allocation;
	void* memLoc;
};
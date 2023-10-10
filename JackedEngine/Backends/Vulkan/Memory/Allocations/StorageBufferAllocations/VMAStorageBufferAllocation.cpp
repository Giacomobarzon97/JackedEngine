#include "VMAStorageBufferAllocation.h"

VMAStorageBufferAllocation::VMAStorageBufferAllocation(const VMAAllocator& allocator, const uint32_t elementSize, const uint32_t nElements) :
	BaseStorageBufferAllocation(elementSize, nElements),
	allocator(allocator)
{
	allocator.CreateBuffer(buffer, allocation, elementSize * nElements, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	allocator.MapMemory(allocation, memLoc);
}

VMAStorageBufferAllocation::~VMAStorageBufferAllocation() {
	allocator.UnMapMemory(allocation);
	allocator.DestroyBuffer(buffer, allocation);
}

void VMAStorageBufferAllocation::UpdateBuffer(const void* data, const uint32_t nElements) const {
	memcpy(memLoc, data, elementSize * nElements);
}
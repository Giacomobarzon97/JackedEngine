#include "VMAUniformAllocation.h"

VMAUniformAllocation::VMAUniformAllocation(const VMAAllocator& allocator, const uint32_t bufferSize) :
	allocator(allocator),
	bufferSize(bufferSize)
{
	allocator.CreateBuffer(buffer, allocation, bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	allocator.MapMemory(allocation, memLoc);
}

VMAUniformAllocation::~VMAUniformAllocation() {
	allocator.UnMapMemory(allocation);
	allocator.DestroyBuffer(buffer, allocation);
}

void VMAUniformAllocation::UpdateBuffer(const void* data) const {
	memcpy(memLoc, data, bufferSize);
}
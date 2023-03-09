#include "VMAUniformBufferAllocation.h"

VMAUniformBufferAllocation::VMAUniformBufferAllocation(const VMAAllocator& allocator, const size_t bufferSize) :
	allocator(allocator),
	bufferSize(bufferSize)
{
	allocator.CreateBuffer(buffer, allocation, bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	allocator.MapMemory(allocation, memLoc);
}

VMAUniformBufferAllocation::~VMAUniformBufferAllocation() {
	allocator.UnMapMemory(allocation);
	allocator.DestroyBuffer(buffer, allocation);
}

void VMAUniformBufferAllocation::UpdateBuffer(const void* data) const {
	memcpy(memLoc, data, bufferSize);
}
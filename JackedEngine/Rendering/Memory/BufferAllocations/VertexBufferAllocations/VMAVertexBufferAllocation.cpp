#include "VMAVertexBufferAllocation.h"

VMAVertexBufferAllocation::VMAVertexBufferAllocation(const VMAAllocator& allocator, const void* data, const size_t dataSize) :
	allocator(allocator)
{
	VkBuffer stagingBuffer;
	VmaAllocation stagingAllocation;
	void* stagingMemLoc;

	allocator.CreateBuffer(stagingBuffer, stagingAllocation, dataSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	allocator.MapMemory(stagingAllocation, stagingMemLoc);
	memcpy(stagingMemLoc, data, dataSize);
	allocator.UnMapMemory(stagingAllocation);
	allocator.CreateBuffer(buffer, allocation, dataSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	allocator.CopyBuffer(stagingBuffer, buffer, dataSize);
	allocator.DestroyBuffer(stagingBuffer, stagingAllocation);
}

VMAVertexBufferAllocation::~VMAVertexBufferAllocation() {
	allocator.DestroyBuffer(buffer, allocation);
}
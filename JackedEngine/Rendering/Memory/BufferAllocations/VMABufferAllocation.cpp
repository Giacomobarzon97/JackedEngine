#include "VMABufferAllocation.h"

VMABufferAllocation::VMABufferAllocation(const VMAAllocator& allocator, const void* data, const size_t dataSize) :
	allocator(allocator)
{
	VkBuffer stagingBuffer;
	VmaAllocation stagingAllocation;
	allocator.CreateBuffer(stagingBuffer, stagingAllocation, dataSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	allocator.MapMemory(stagingAllocation,data,dataSize);
	allocator.CreateBuffer(buffer, allocation, dataSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	allocator.copyBuffer(stagingBuffer, buffer, dataSize);
	allocator.DestroyBuffer(stagingBuffer, stagingAllocation);
}

VMABufferAllocation::~VMABufferAllocation() {
	allocator.DestroyBuffer(buffer, allocation);
}

const VkDeviceSize VMABufferAllocation::GetOffset() const {
	return allocator.GetAllocationOffset(allocation);
}
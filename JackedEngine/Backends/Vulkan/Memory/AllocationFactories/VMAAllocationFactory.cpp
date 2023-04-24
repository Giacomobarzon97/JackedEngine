#include "VMAAllocationFactory.h"

VMAAllocationFactory::VMAAllocationFactory(const Device& device) :
	allocator(device)
{}

VMAAllocationFactory::~VMAAllocationFactory(){}

const VMABufferAllocation* VMAAllocationFactory::CreateBufferAllocation(const void* data, const uint32_t dataSize, VkBufferUsageFlags usage) const {
	return new VMABufferAllocation(allocator, data, dataSize, usage);
}

const VMAUniformAllocation* VMAAllocationFactory::CreateUniformAllocation(const uint32_t bufferSize) const {
	return new VMAUniformAllocation(allocator, bufferSize);
}

const VMAImageAllocation* VMAAllocationFactory::CreateImageAllocation(const std::vector<const void*> data, const int width, const int height, VkImageViewType imageViewType, VkImageCreateFlags flags) const {
	return new VMAImageAllocation(allocator, data, width, height, imageViewType, flags);
}

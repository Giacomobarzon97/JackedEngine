#include "VMAAllocationFactory.h"

VMAAllocationFactory::VMAAllocationFactory(const Device& device) :
	allocator(device)
{}

VMAAllocationFactory::~VMAAllocationFactory(){}

const VMAVertexBufferAllocation* VMAAllocationFactory::CreateVertexBufferAllocation(const void* data, const size_t dataSize) const {
	return new VMAVertexBufferAllocation(allocator, data, dataSize);
}

const VMAIndexBufferAllocation* VMAAllocationFactory::CreateIndexBufferAllocation(const void* data, const size_t dataSize) const {
	return new VMAIndexBufferAllocation(allocator, data, dataSize);
}

const VMAUniformBufferAllocation* VMAAllocationFactory::CreateUniformBufferAllocation(const size_t bufferSize) const {
	return new VMAUniformBufferAllocation(allocator, bufferSize);
}

#include "VMAAllocationFactory.h"

VMAAllocationFactory::VMAAllocationFactory(const Device& device) :
	allocator(device)
{}

VMAAllocationFactory::~VMAAllocationFactory(){}

const VMAVertexBufferAllocation* VMAAllocationFactory::CreateVertexBufferAllocation(const void* data, const uint32_t dataSize) const {
	return new VMAVertexBufferAllocation(allocator, data, dataSize);
}

const VMAIndexBufferAllocation* VMAAllocationFactory::CreateIndexBufferAllocation(const void* data, const uint32_t dataSize) const {
	return new VMAIndexBufferAllocation(allocator, data, dataSize);
}

const VMAUniformAllocation* VMAAllocationFactory::CreateUniformAllocation(const uint32_t bufferSize) const {
	return new VMAUniformAllocation(allocator, bufferSize);
}

const VMAImage2DAllocation* VMAAllocationFactory::CreateImage2DAllocation(const void* data, const int width, const int height) const {
	return new VMAImage2DAllocation(allocator, data, width, height);
}

const VMACubemapAllocation* VMAAllocationFactory::CreateCubemapAllocation(const std::array<const void*, 6> data, const int width, const int height) const {
	return new VMACubemapAllocation(allocator, data, width, height);
}
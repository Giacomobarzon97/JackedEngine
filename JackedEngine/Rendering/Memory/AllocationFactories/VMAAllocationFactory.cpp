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

const VMAUniformBufferAllocation* VMAAllocationFactory::CreateUniformBufferAllocation(const uint32_t bufferSize) const {
	return new VMAUniformBufferAllocation(allocator, bufferSize);
}

const VMAImageBufferAllocation* VMAAllocationFactory::CreateImageBufferAllocation(const void* data, const int width, const int height) const {
	return new VMAImageBufferAllocation(allocator, data, width, height);
}

const VMACubemapBufferAllocation* VMAAllocationFactory::CreateCubemapBufferAllocation(const void* frontFaceData, const void* backFaceData, const void* upFaceData, const void* downFaceData, const void* rightFaceData, const void* leftFaceData, const int width, const int height) const {
	return new VMACubemapBufferAllocation(allocator, frontFaceData, backFaceData, upFaceData, downFaceData, rightFaceData, leftFaceData, width, height);
}

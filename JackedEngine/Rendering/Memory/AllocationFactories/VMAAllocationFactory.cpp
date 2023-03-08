#include "VMAAllocationFactory.h"

VMAAllocationFactory::VMAAllocationFactory(const Device& device) :
	allocator(device)
{}

const VMABufferAllocation* VMAAllocationFactory::CreateBufferAllocation(const void* data, const size_t dataSize) const {
	return new VMABufferAllocation(allocator, data, dataSize);
}

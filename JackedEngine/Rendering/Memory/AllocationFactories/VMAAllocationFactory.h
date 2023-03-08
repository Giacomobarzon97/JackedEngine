#pragma once
#include "Rendering/Device.h"
#include "Rendering/Memory/AllocationFactories/BaseAllocationFactory.h"
#include "Rendering/Memory/BufferAllocations/VMABufferAllocation.h"

class VMAAllocationFactory : public BaseAllocationFactory {
public:
	VMAAllocationFactory(const Device& device);
	VMAAllocationFactory(VMAAllocationFactory&) = delete;
	VMAAllocationFactory& operator=(VMAAllocationFactory&) = delete;

	virtual const VMABufferAllocation* CreateBufferAllocation(const void* data, const size_t dataSize) const override;

private:
	VMAAllocator allocator;
};
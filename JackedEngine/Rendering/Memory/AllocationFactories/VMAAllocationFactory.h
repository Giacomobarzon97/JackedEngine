#pragma once
#include "Rendering/Device.h"
#include "Rendering/Memory/AllocationFactories/BaseAllocationFactory.h"
#include "Rendering/Memory/BufferAllocations/VertexBufferAllocations/VMAVertexBufferAllocation.h"
#include "Rendering/Memory/BufferAllocations/IndexBufferAllocations/VMAIndexBufferAllocation.h"

class VMAAllocationFactory : public BaseAllocationFactory {
public:
	VMAAllocationFactory(const Device& device);
	VMAAllocationFactory(VMAAllocationFactory&) = delete;
	virtual ~VMAAllocationFactory() override;

	VMAAllocationFactory& operator=(VMAAllocationFactory&) = delete;

	virtual const VMAVertexBufferAllocation* CreateVertexBufferAllocation(const void* data, const size_t dataSize) const override;
	virtual const VMAIndexBufferAllocation* CreateIndexBufferAllocation(const void* data, const size_t dataSize) const override;

private:
	VMAAllocator allocator;
};
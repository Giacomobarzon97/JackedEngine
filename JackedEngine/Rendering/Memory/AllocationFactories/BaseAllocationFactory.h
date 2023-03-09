#pragma once
#include "Rendering/Memory/BufferAllocations/VertexBufferAllocations/BaseVertexBufferAllocation.h"
#include "Rendering/Memory/BufferAllocations/IndexBufferAllocations/BaseIndexBufferAllocation.h"


class BaseAllocationFactory {
public:
	virtual const BaseVertexBufferAllocation* CreateVertexBufferAllocation(const void* data, const size_t dataSize) const = 0;
	virtual const BaseIndexBufferAllocation* CreateIndexBufferAllocation(const void* data, const size_t dataSize) const = 0;

	virtual ~BaseAllocationFactory();
};
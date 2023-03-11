#pragma once
#include "Rendering/Memory/BufferAllocations/VertexBufferAllocations/BaseVertexBufferAllocation.h"
#include "Rendering/Memory/BufferAllocations/IndexBufferAllocations/BaseIndexBufferAllocation.h"
#include "Rendering/Memory/BufferAllocations/UniformBufferAllocations/BaseUniformBufferAllocation.h"
#include "Rendering/Memory/BufferAllocations/ImageBufferAllocations/BaseImageBufferAllocation.h"

class BaseAllocationFactory {
public:
	virtual const BaseVertexBufferAllocation* CreateVertexBufferAllocation(const void* data, const size_t dataSize) const = 0;
	virtual const BaseIndexBufferAllocation* CreateIndexBufferAllocation(const void* data, const size_t dataSize) const = 0;
	virtual const BaseUniformBufferAllocation* CreateUniformBufferAllocation(const size_t dataSize) const = 0;
	virtual const BaseImageBufferAllocation* CreateImageBufferAllocation(const void* data, const int width, const int height) const = 0;

	virtual ~BaseAllocationFactory();
};
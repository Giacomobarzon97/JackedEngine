#pragma once
#include <vector>
#include "Backends/Vulkan/Memory/Allocations/IndexBufferAllocations/BaseIndexBufferAllocation.h"
#include "Backends/Vulkan/Memory/Allocations/VertexBufferAllocations/BaseVertexBufferAllocation.h"
#include "Backends/Vulkan/Memory/Allocations/UniformAllocations/BaseUniformAllocation.h"
#include "Backends/Vulkan/Memory/Allocations/ImageAllocations/BaseImageAllocation.h"

class BaseAllocationFactory {
public:
	virtual const BaseIndexBufferAllocation* CreateIndexBufferAllocation(const void* data, const uint32_t dataSize) const = 0;
	virtual const BaseVertexBufferAllocation* CreateVertexBufferAllocation(const void* data, const uint32_t dataSize) const = 0;
	virtual const BaseUniformAllocation* CreateUniformAllocation(const uint32_t dataSize) const = 0;
	virtual const BaseImageAllocation* CreateImageAllocation(const std::vector<const void*> data, const int width, const int height, VkImageViewType imageViewType, VkImageCreateFlags flags) const = 0;

	virtual ~BaseAllocationFactory();
};
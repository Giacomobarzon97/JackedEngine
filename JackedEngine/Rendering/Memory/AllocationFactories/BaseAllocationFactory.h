#pragma once
#include <vector>
#include "Rendering/Memory/Allocations/BufferAllocations/BaseBufferAllocation.h"
#include "Rendering/Memory/Allocations/UniformAllocations/BaseUniformAllocation.h"
#include "Rendering/Memory/Allocations/ImageAllocations/BaseImageAllocation.h"

class BaseAllocationFactory {
public:
	virtual const BaseBufferAllocation* CreateBufferAllocation(const void* data, const uint32_t dataSize, VkBufferUsageFlags usage) const = 0;
	virtual const BaseUniformAllocation* CreateUniformAllocation(const uint32_t dataSize) const = 0;
	virtual const BaseImageAllocation* CreateImageAllocation(const std::vector<const void*> data, const int width, const int height, VkImageViewType imageViewType, VkImageCreateFlags flags) const = 0;

	virtual ~BaseAllocationFactory();
};
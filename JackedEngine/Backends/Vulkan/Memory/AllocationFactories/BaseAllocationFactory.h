#pragma once
#include <vector>
#include "Backends/Vulkan/Memory/Allocations/IndexBufferAllocations/BaseIndexBufferAllocation.h"
#include "Backends/Vulkan/Memory/Allocations/VertexBufferAllocations/BaseVertexBufferAllocation.h"
#include "Backends/Vulkan/Memory/Allocations/UniformAllocations/BaseUniformAllocation.h"
#include "Backends/Vulkan/Memory/Allocations/Image2DAllocations/BaseImage2DAllocation.h"
#include "Backends/Vulkan/Memory/Allocations/CubemapAllocations/BaseCubemapAllocation.h"

class BaseAllocationFactory {
public:
	virtual const BaseIndexBufferAllocation* CreateIndexBufferAllocation(const void* data, const uint32_t dataSize) const = 0;
	virtual const BaseVertexBufferAllocation* CreateVertexBufferAllocation(const void* data, const uint32_t dataSize) const = 0;
	virtual const BaseUniformAllocation* CreateUniformAllocation(const uint32_t dataSize) const = 0;
	virtual const BaseImage2DAllocation* CreateImage2DAllocation(const void* data, const int width, const int height) const = 0;
	virtual const BaseCubemapAllocation* CreateCubemapAllocation(const std::array<const void*, 6> data, const int width, const int height) const = 0;

	virtual ~BaseAllocationFactory();
};